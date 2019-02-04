#pragma once
#include <memory>
#include <functional>
#include <QtCore/QtGlobal>


QT_FORWARD_DECLARE_CLASS(QObject)
QT_FORWARD_DECLARE_CLASS(QQuickItem)
QT_FORWARD_DECLARE_CLASS(QQmlComponent)


namespace Backbone {

class QmlComponentsCache;
using QmlComponentsCachePtr = std::shared_ptr<QmlComponentsCache>;

class QmlInjector;
using QmlInjectorPtr = std::shared_ptr<QmlInjector>;

class Router;
using RouterPtr = std::shared_ptr<Router>;

using QmlInjectorFactory = std::function<QObject*()>;

} // namespace Backbone