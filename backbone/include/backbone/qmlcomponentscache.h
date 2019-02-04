#pragma once
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QHash>
#include <portable_concurrency/future_fwd>
#include "incubator.h"

QT_FORWARD_DECLARE_CLASS(QQmlEngine)
QT_FORWARD_DECLARE_CLASS(QQmlComponent)


namespace Backbone {


class QmlComponentsCache
    : public QObject
{
    Q_OBJECT
public:
    QmlComponentsCache(QQmlEngine * engine);
    ~QmlComponentsCache() = default;

    pc::future<QQmlComponent*> resolve(const QUrl & url);

public slots:
    // todo: do I really need it?
    void trimMemory();

private:
    QQmlEngine * const engine_ = nullptr;
    QHash<QUrl, QQmlComponent*> cache_;
};


} // namespace Backbone
