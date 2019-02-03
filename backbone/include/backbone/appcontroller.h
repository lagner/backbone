#pragma once
#include <QtCore/QObject>
#include <backbone/pagepresenter.h>
#include <backbone/qmlinjector.h>
#include "global.h"
#include <QtQml/QJSValue>


namespace Backbone {


class AppController
    : public QObject
{
    Q_OBJECT
public:
    AppController(
        QmlInjectorUnq injector,
        QmlComponentsCache * cache,
        Router * router,
        QObject * parent = nullptr);

    Backbone::PagePresenter * resolvePresenter(const QString & name);


    Q_INVOKABLE void create(const QUrl & componentUrl, QJSValue callback);

    QObject * create(QQmlComponent * component);

private:
    const QmlInjectorUnq injector_;
    QmlComponentsCache * cache_ = nullptr;
    Router * router_ = nullptr;
};


} // namespace Backbone
