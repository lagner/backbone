#pragma once
#include <QtCore/QObject>
#include "appcontroller.h"
#include "router.h"


namespace Backbone {


class QmlGlobalScope
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AppController* appController READ appController CONSTANT FINAL)
    Q_PROPERTY(Router* router READ router CONSTANT FINAL)

public:
    QmlGlobalScope(AppController * controller, Router * router, QObject * parent);

    AppController * appController() const { return appController_; }

    Router * router() const { return router_; }

    QmlInjectorPtr injector() const { return !!router_ ? router_->injector() : nullptr; }

private:
    AppController * appController_ = nullptr;
    Router * router_ = nullptr;
};


} // namespace Backbone
