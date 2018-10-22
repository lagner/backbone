#include <backbone/router.h>
#include <backbone/container.h>
#include <QtCore/QDebug>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlProperty>
#include <QtQuickTemplates2/private/qquickstackview_p.h>
#include <QtGui/QWindow>
#include <backbone/args.h>


namespace {

QQuickStackView * stackView(QObject * ptr)
{
    return qobject_cast<QQuickStackView*>(ptr);
}

} // namespace


namespace Backbone {


Router::Router(QQmlApplicationEngine * engine, QmlComponentsCache * cache, QUrl windowUrl)
    : QObject(engine)
    , cache_(cache)
{
    if (!engine)
    {
        qFatal("impossible to work without QmlEngine");
    }
    if (!cache)
    {
        qFatal("impossible to work without QmlComponentsCache");
    }

    // FIXME: wtf?
    // we need AppFrame or smth...
    connect(
        engine, &QQmlApplicationEngine::objectCreated,
        this, &Router::onWindowReady);

    Q_UNUSED(windowUrl);
}


/*
void Router::push(QString name, QVariantMap members)
{
    auto args = ArgsPtr::create(std::move(members));

    ArgsWeakWrapper qmlArgs;
    qmlArgs.args = args;

    emit pushPage(std::move(name), qmlArgs);
}
*/


void Router::push(QString url, QVariantMap args)
{
    auto incubator = cache_->create(QUrl(url), [a = std::move(args)] (QObject * object) mutable {
        auto item = qobject_cast<Container*>(object);
        if (!item)
        {
            qFatal("try to push object on a stack");
        }
        item->setArgs(std::move(a));
    });

    connect(incubator, &Incubator::ready, this, [this] (QObject * object, QString errorString) {
        if (!errorString.isEmpty())
        {
            qDebug() << "component error: " << errorString;
            return;
        }

        auto item = static_cast<QQuickItem*>(object);
        pages_.push(item);
        emit pushPage(item);
    });
    connect(incubator, &Incubator::ready, incubator, &Incubator::deleteLater);
}


void Router::pop()
{
    emit popPage();
}


int Router::depth() const
{
    if (!navigationView_)
        return 0;

    return stackView(navigationView_)->depth();
}


void Router::onWindowReady(QObject * root, const QUrl&)
{
    qDebug() << "window is ready";

    // TODO: disconnect
    if (!root)
        return;

    QQmlProperty stackViewGetter(root, QStringLiteral("stackView"));
    navigationView_ = stackViewGetter.read().value<QObject*>();

    if (!navigationView_)
    {
        qDebug() << "root view has no property stackView";
        return;
    }

    auto sv = stackView(navigationView_);
    if (!sv)
    {
        qDebug() << "property is not stackView";
        return;
    }

    qDebug() << "it has pages: " << sv->depth();
}


} // namespace Backbone
