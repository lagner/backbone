#pragma once
#include <string>
#include <unordered_map>
#include "fwd.h"

// todo: you can better
#include <QtQml/qqml.h>


namespace Backbone {


class QmlInjectorBuilder
{
public:
    QmlInjectorBuilder(char const * const ns /* = AppName */);

    template<class TItem>
    QmlInjectorBuilder & add(const char * qmlName, QmlInjectorFactory creator);

    QmlInjectorPtr build();

private:
    char const * const qmlNamespace_;
    std::unordered_map<std::string, QmlInjectorFactory> items_;
};


template<typename TItem>
QmlInjectorBuilder & QmlInjectorBuilder::add(const char * qmlName, QmlInjectorFactory creator)
{
    qmlRegisterUncreatableType<TItem>(qmlNamespace_, 1, 0, qmlName, "should be created in C++");

    std::string name = std::string(TItem::staticMetaObject.className()) + "*";

    items_.emplace(std::move(name), std::move(creator));

    return *this;
}


} // namespace Backbone

