#pragma once
#include <QtCore/QDebug>
#include <QtCore/QHash>
#include <QtQml/QQmlEngine>
#include <string>
#include <unordered_map>
#include "qmlinjector.h"


namespace Backbone {


class QmlInjectorBuilder
{
public:
    QmlInjectorBuilder(QLatin1String ns /* = AppName */);

    template<class TItem>
    QmlInjectorBuilder & add(const char * qmlName, InjectedObjectCreator creator);

    QmlInjectorUnq build();

private:
    const QLatin1String qmlNamespace_;
    std::unordered_map<std::string, InjectedObjectCreator> items_;
};


template<typename TItem>
QmlInjectorBuilder & QmlInjectorBuilder::add(const char * qmlName, InjectedObjectCreator creator)
{
    qmlRegisterUncreatableType<TItem>(qmlNamespace_.data(), 1, 0, qmlName, "should be created in C++");

    std::string name = std::string(TItem::staticMetaObject.className()) + "*";
    qDebug() << "register: " << name.c_str();

    items_.emplace(std::move(name), std::move(creator));

    return *this;
}


} // namespace Backbone



