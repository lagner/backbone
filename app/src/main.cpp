#include <backbone/appcontroller.h>
#include <backbone/global.h>
#include <backbone/qmlcomponentscache.h>
#include <backbone/qmlglobalscope.h>
#include <backbone/qmlinjectorbuilder.h>
#include <backbone/qmlinjector.h>
#include <backbone/fwd.h>
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


Backbone::QmlInjectorPtr registerTypes()
{
    Backbone::import();
    Backbone::QmlInjectorBuilder builder { appQmlNamespace };

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
    auto cache = std::make_shared<Backbone::QmlComponentsCache>(&engine);

    auto router = new Backbone::Router(cache, injector, &engine);
    auto controller = new Backbone::AppController(&engine);

    auto scope = new Backbone::QmlGlobalScope(controller, router, &engine);

    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextObject(scope);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
