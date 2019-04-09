#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <QtCore/QtGlobal>
#include <QtCore/QVariant>
#include <portable_concurrency/functional_fwd>


QT_FORWARD_DECLARE_CLASS(QObject)
QT_FORWARD_DECLARE_CLASS(QQuickItem)
QT_FORWARD_DECLARE_CLASS(QQmlComponent)


namespace Backbone {

class QmlComponentsCache;
using QmlComponentsCachePtr = std::shared_ptr<QmlComponentsCache>;

class Injector;
using InjectorPtr = std::shared_ptr<Injector>;

class Router;
using RouterPtr = std::shared_ptr<Router>;

using InjectorTypeId = std::string;
using InjectorFactory = pc::unique_function<std::unique_ptr<QObject>(QVariant)>;
using InjectorContextProvider = pc::unique_function<QVariant(const InjectorTypeId &)>;

using FactoryCollection = std::map<InjectorTypeId, InjectorFactory>;

} // namespace Backbone
