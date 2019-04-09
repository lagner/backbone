#include <backbone/appcontroller.h>
#include <backbone/global.h>
#include <backbone/qmlcomponentscache.h>
#include <backbone/qmlglobalscope.h>
#include <backbone/injectorbuilder.h>
#include <backbone/injector.h>
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
#include <portable_concurrency/functional>
#include <portable_concurrency/future>

#include "presenters/detailpagepresenter.h"
#include "presenters/indexpagepresenter.h"
#include "presenters/searchpagepresenter.h"
#include "presenters/branchpresenter.h"
#include "presenters/schedulepresenter.h"
#include "types.h"


namespace {


const char * appQmlNamespace = "App.Presenters";


} // namespace


Backbone::InjectorPtr registerTypes()
{
    Backbone::import();
    Backbone::InjectorBuilder builder { appQmlNamespace };

    builder.add<IndexPagePresenter>([] (QVariant) {
        return std::make_unique<IndexPagePresenter>();
    });
    builder.add<DetailPagePresenter>([] (QVariant) {
        return std::make_unique<DetailPagePresenter>();
    });
    builder.add<SearchPagePresenter>([] (QVariant) {
        return std::make_unique<SearchPagePresenter>();
    });
    builder.add<BranchPresenter>([] (QVariant) {
        return std::make_unique<BranchPresenter>();
    });
    builder.add<SchedulePresenter>([] (QVariant) {
        return std::make_unique<SchedulePresenter>();
    });

    // @uri App.Presenters
    qmlRegisterUncreatableType<BranchPresenter>("App.Presenters", 1, 0, "BranchPresenter", "");
    qmlRegisterUncreatableType<SchedulePresenter>("App.Presenters", 1, 0, "SchedulePresenter", "");

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

    QQmlContext * rootContext = engine.rootContext();
    auto scope = new Backbone::QmlGlobalScope(controller, router, rootContext);

    rootContext->setContextObject(scope);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
