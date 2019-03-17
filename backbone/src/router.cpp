#include <backbone/executors.h>
#include <backbone/qmlcomponentscache.h>
#include <backbone/qmlinjector.h>
#include <backbone/router.h>
#include <backbone/page.h>
#include <backbone/pagepresenter.h>
#include <portable_concurrency/future>
#include <QtCore/QDebug>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickItem>


namespace {

} // namespace


namespace Backbone {


Router::Router(QmlComponentsCachePtr cache, QmlInjectorPtr injector, QObject * parent)
    : QObject(parent)
    , cache_(cache)
    , injector_(injector)
{
    if (!cache)
    {
        qFatal("impossible to work without QmlComponentsCache");
    }
    if (!injector)
    {
        qFatal("impossible to work without QmlInjector");
    }
}


void Router::createPage(const QUrl & uri, QJSValue callback)
{
    cache_->resolve(uri)
        .then(executor(this),
              [this, callback = std::move(callback)] (pc::future<QQmlComponent*> future) mutable {
                  QJSValue arg;
                  try {
                      auto component = future.get();
                      Q_ASSERT(component);

                      auto engine = component->engine();
                      Q_ASSERT(engine);
                      auto context = engine->rootContext();
                      Q_ASSERT(context);

                      auto object = component->beginCreate(context);
                      // todo: do we need parent?
                      if (auto injected = injector_->inject(object, QStringLiteral("presenter")))
                      {
                          if (auto presenter = qobject_cast<PagePresenter*>(injected))
                          {
                              auto view = qobject_cast<QQuickItem*>(object);
                              presenter->onCreate(view, QVariantMap());
                          }
                      }
                      component->completeCreate();

                      arg = engine->toScriptValue(object);
                  } catch (const std::exception & ex) {
                      qWarning() << "Creating component exception: " << ex.what();
                      // todo: arg as error
                  }

                  QJSValueList args;
                  args << arg;

                  callback.call(args);

              }).detach();
}


} // namespace Backbone
