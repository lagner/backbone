#pragma once
#include "fwd.h"


QT_FORWARD_DECLARE_CLASS(QStringList)


namespace Backbone {


class PagePresenter;


class Injector
{
public:
    Injector(std::vector<std::pair<InjectorTypeId, InjectorFactory>> creators)
        : creators_(std::move(creators))
    {}

    bool inject(QObject * object, const QVariant & context) const;

    bool inject(QObject * object, InjectorContextProvider provider) const;

private:
    const std::vector<std::pair<InjectorTypeId, InjectorFactory>> creators_;
};


} // namespace Backbone
