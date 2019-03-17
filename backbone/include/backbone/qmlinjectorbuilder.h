#pragma once
#include <string>
#include <QtCore/QDebug>
#include "fwd.h"

// todo: you can better
#include <QtQml/qqml.h>


namespace Backbone {


class QmlInjectorBuilder
{
public:
    QmlInjectorBuilder(char const * const ns /* = AppName */);

    template<class TItem>
    QmlInjectorBuilder & add(QmlInjectorFactory creator);

    QmlInjectorPtr build();

private:
    char const * const qmlNamespace_;
    FactoryCollection items_;
};


template<typename TItem>
QmlInjectorBuilder & QmlInjectorBuilder::add(QmlInjectorFactory creator)
{
    auto className = TItem::staticMetaObject.className();

    qmlRegisterUncreatableType<TItem>(qmlNamespace_, 1, 0, className, "should be created in C++");

    std::string name = std::string(className) + "*";

    items_.emplace(std::move(name), std::move(creator));

    return *this;
}


} // namespace Backbone

