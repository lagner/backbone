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
        InjectorPtr injector,
        QObject * parent);

    // todo: loading page property

    InjectorPtr injector() const { return injector_; }

public slots:
    // todo: bool?
    void createPage(const QUrl & uri, QJSValue callback);

private:
    QmlComponentsCachePtr cache_;
    InjectorPtr injector_;
};


} // namespace Backbone
