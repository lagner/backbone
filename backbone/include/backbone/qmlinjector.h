#pragma once
#include "fwd.h"


QT_FORWARD_DECLARE_CLASS(QStringList)


namespace Backbone {


class PagePresenter;


class QmlInjector
{
public:
    QmlInjector(FactoryCollection creators)
        : creators_(std::move(creators))
    {}

    bool inject(QObject * object, const QStringList & properties) const;

    QObject * inject(QObject * object, const QString & property) const;

    void inject(QObject * object, const QVariant & ctx) const;

private:
    const FactoryCollection creators_;
};


} // namespace Backbone
