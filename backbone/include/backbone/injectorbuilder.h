#pragma once
#include <string>
#include <QtCore/QDebug>
#include "fwd.h"

// todo: you can better
#include <QtQml/qqml.h>


namespace Backbone {


class InjectorBuilder
{
public:
    InjectorBuilder(char const * const ns /* = AppName */);

    template<class TItem>
    InjectorBuilder & add(InjectorFactory creator);

    InjectorPtr build();

private:
    char const * const qmlNamespace_;
    std::map<InjectorTypeId, InjectorFactory> items_;
};


template<typename TItem>
InjectorBuilder & InjectorBuilder::add(InjectorFactory creator)
{
    auto className = TItem::staticMetaObject.className();

    qmlRegisterUncreatableType<TItem>(qmlNamespace_, 1, 0, className, "should be created in C++");

    std::string name = std::string(className) + "*";

    items_.emplace(std::move(name), std::move(creator));

    return *this;
}


} // namespace Backbone

