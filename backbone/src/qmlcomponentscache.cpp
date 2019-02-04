#include <backbone/qmlcomponentscache.h>
#include <backbone/executors.h>
#include <QtCore/QUrl>
#include <QtCore/QDebug>
#include <QtCore/QPointer>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <portable_concurrency/future>


namespace Backbone {


QmlComponentsCache::QmlComponentsCache(QQmlEngine * engine)
    : QObject(nullptr)
    , engine_(engine)
{
    if (!engine_)
    {
        qFatal("could not create components without QQmlEngine");
    }
}


pc::future<QQmlComponent*> QmlComponentsCache::resolve(const QUrl & url)
{
    using Self = QPointer<QmlComponentsCache>;

    const auto it = cache_.find(url);
    if (it != cache_.cend())
    {
        qDebug() << "component found in cache";
        return pc::make_ready_future(it.value());
    }

    auto component = new QQmlComponent(
        engine_, url, QQmlComponent::Asynchronous, this);

    if (QQmlComponent::Ready == component->status())
    {
        qDebug() << "created synchronous. Return ready from cache";
        cache_.insert(url, component);
        return pc::make_ready_future(component);
    }

    struct IncubationMeta {
        QMetaObject::Connection connection;
        QQmlComponent * component;
        pc::promise<QQmlComponent*> promise;
    };

    auto incubator = std::make_shared<IncubationMeta>();

    incubator->component = component;
    incubator->connection = connect(
        component,
        &QQmlComponent::statusChanged,
        this,
        [incubator] (QQmlComponent::Status status) {
            if (QQmlComponent::Loading == status ||
                QQmlComponent::Null == status)
            {
                return;
            }
            else if (QQmlComponent::Ready == status)
            {
                incubator->promise.set_value(incubator->component);
            }
            else if (QQmlComponent::Error == status)
            {
                auto error = incubator->component->errorString().toStdString();
                auto ex = std::make_exception_ptr(std::runtime_error(error));

                incubator->promise.set_exception(ex);
            }
            QObject::disconnect(incubator->connection);
        });
    Q_ASSERT(incubator->connection);

    return incubator->promise.get_future()
        .next([self = Self(this)] (QQmlComponent * component) {
            if (self) {
                self->cache_.insert(component->url(), component);
            }
            return component;
        });
}


void QmlComponentsCache::trimMemory()
{
    cache_.clear();
}


} // namespace Backbone
