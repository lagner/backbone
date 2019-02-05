#pragma once
#include <unordered_map>
#include "fwd.h"


QT_FORWARD_DECLARE_CLASS(QStringList)


namespace Backbone {


class PagePresenter;


using TypeName = std::string;
using FactoryCollection = std::unordered_map<TypeName, QmlInjectorFactory>;


class QmlInjector
{
public:
    QmlInjector(FactoryCollection creators)
        : creators_(std::move(creators))
    {}

    bool inject(QObject * object, const QStringList & properties) const;

    QObject * inject(QObject * object, const QString & property) const;

private:
    const FactoryCollection creators_;
};


} // namespace Backbone
