#pragma once
#include <QtCore/QObject>
#include <QtQml/QJSValue>
#include "fwd.h"


namespace Backbone {


class Router
    : public QObject
{
    Q_OBJECT

public:
    Router(
        QmlComponentsCachePtr cache,
        QmlInjectorPtr injector,
        QObject * parent);

    // todo: loading page property

    QmlInjectorPtr injector() const { return injector_; }

public slots:
    // todo: bool?
    void createPage(const QUrl & uri, QJSValue callback);

private:
    QmlComponentsCachePtr cache_;
    QmlInjectorPtr injector_;
};


} // namespace Backbone
