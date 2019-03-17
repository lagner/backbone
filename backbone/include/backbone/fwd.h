#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <QtCore/QtGlobal>
#include <QtCore/QVariant>


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

using TypeName = std::string;
using QmlInjectorFactory = std::function<QObject*(QVariant)>;
using FactoryCollection = std::map<TypeName, QmlInjectorFactory>;

} // namespace Backbone
