#include <backbone/appcontroller.h>
#include <backbone/executors.h>
#include <backbone/pagepresenter.h>
#include <QtCore/QDebug>
#include <QtQml/QJSValue>
#include <portable_concurrency/future>


namespace Backbone {


AppController::AppController(
        QmlInjectorUnq injector,
        QmlComponentsCache * cache,
        Router * router,
        QObject * parent)
    : QObject(parent)
    , injector_(std::move(injector))
    , cache_(cache)
    , router_(router)
{
    Q_ASSERT(cache);
}


PagePresenter * AppController::resolvePresenter(const QString & def)
{
    const auto name = def.toStdString();
    return static_cast<PagePresenter*>(injector_->create(name));
}


void AppController::create(
    const QUrl & componentUrl,
    QJSValue callback)
{
    Q_ASSERT(callback.isCallable());
    Q_ASSERT(cache_);

    cache_->resolve(componentUrl)
        .then(executor(this),
            [this, callback = std::move(callback)] (pc::future<QQmlComponent*> future) mutable {
                QJSValue arg;
                try {
                    auto component = future.get();
                    auto object = create(component);
                    auto engine = component->engine();
                    arg = engine->toScriptValue(object);

                } catch (const std::exception & ex) {
                    qWarning() << "Creating component exception: " << ex.what();
                }

                QJSValueList args;
                args << arg;

                callback.call(args);

            }).detach();
}


QObject * AppController::create(QQmlComponent * component)
{
    if (QQmlComponent::Ready != component->status())
    {
        throw std::runtime_error("Try to inject but component is not ready");
    }

    auto engine = component->engine();
    auto context = engine->rootContext();

    auto object = component->beginCreate(context);
    if (auto presenter = injector_->injectPresenter(object))
    {
        presenter->setRouter(router_);
    }

    component->completeCreate();
    return object;
}


} // namespace Backbone
