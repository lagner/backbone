#include <backbone/appcontroller.h>
#include <backbone/global.h>
#include <backbone/qmlcomponentscache.h>
#include <backbone/qmlglobalscope.h>
#include <backbone/qmlinjectorbuilder.h>
#include <backbone/qmlinjector.h>
#include <QtCore/QDebug>
#include <QtCore/QMetaObject>
#include <QtCore/QObject>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQml/qqml.h>
#include <QtQml/QQmlProperty>
#include <QtQuickControls2/QQuickStyle>
#include <portable_concurrency/future>

#include "presenters/detailpagepresenter.h"
#include "presenters/indexpagepresenter.h"
#include "presenters/searchpagepresenter.h"
#include "types.h"


namespace {


const char * appQmlNamespace = "App.Presenters";


} // namespace



pc::future<std::unique_ptr<QObject>> createObject(QQmlEngine * engine, QUrl & uri, Backbone::QmlInjectorPtr injector)
{
    struct Data {
        pc::promise<std::unique_ptr<QObject>> promise;
        std::unique_ptr<QQmlComponent> component;
        QQmlContext * parentContext = nullptr;
        QMetaObject::Connection connection;
        Backbone::QmlInjectorPtr injector;
    };
    auto data = std::make_shared<Data>();

    data->component = std::make_unique<QQmlComponent>(engine, uri, QQmlComponent::Asynchronous);
    data->connection = QObject::connect(
        data->component.get(),
        &QQmlComponent::statusChanged,
        [data] (QQmlComponent::Status status) {
            if (QQmlComponent::Ready == status)
            {
                auto obj = data->component->beginCreate(data->parentContext);

                QQmlProperty presenterProp(obj, "presenter");
                const auto type = std::string(presenterProp.propertyTypeName());

                auto presenter = data->injector->create(type);

                presenterProp.write(QVariant::fromValue(presenter));
                // todo: handle error
                // todo: inject properties
                data->component->completeCreate();

                data->promise.set_value(std::unique_ptr<QObject>(obj));
                QObject::disconnect(data->connection);
            }
            else if (QQmlComponent::Error == status)
            {
                auto exception = std::make_exception_ptr(
                    std::runtime_error(data->component->errorString().toStdString()));
                data->promise.set_exception(exception);
                QObject::disconnect(data->connection);
            }
        });

    return data->promise.get_future();
}



Backbone::QmlInjectorUnq registerTypes()
{
    Backbone::import();
    Backbone::QmlInjectorBuilder builder { QLatin1String(appQmlNamespace) };

    builder.add<IndexPagePresenter>("IndexPagePresenter", [] {
        return new IndexPagePresenter();
    });
    builder.add<DetailPagePresenter>("DetailPagePresenter", [] {
        return new DetailPagePresenter();
    });
    builder.add<SearchPagePresenter>("SearchPagePresenter", [] {
        return new SearchPagePresenter();
    });

    return builder.build();
}



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle(QStringLiteral("Material"));
    QQmlApplicationEngine engine;

    auto injector = registerTypes();
    auto windowUrl = QUrl(QStringLiteral("qrc:/qml/main.qml"));

    auto cache = new Backbone::QmlComponentsCache(&engine);
    auto router = new Backbone::Router(&engine, cache, std::move(windowUrl));
    auto controller = new Backbone::AppController(std::move(injector), cache, router, &engine);

    auto scope = new Backbone::QmlGlobalScope(controller, router, &engine);

    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextObject(scope);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
