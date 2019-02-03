#pragma once
#include <stack>
#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickItem>
#include "qmlinjector.h"
#include "qmlcomponentscache.h"


namespace Backbone {


class Router
    : public QObject
{
    Q_OBJECT

public:
    Router(
        QQmlApplicationEngine * engine,
        QmlComponentsCache * cache,
        QUrl windowUrl);

    void push(QString page, QVariantMap args);
    void pop();

    int depth() const;

signals:
    void pushUrl(QUrl url);

    // TODO: make it private
    void pushPage(QQuickItem * page);
    void popPage();

    // FIXME: replace for QVariantMap
    // void replace(QString page, Backbone::ArgsWeakWrapper args);

private slots:
    void onWindowReady(QObject * root, const QUrl&);

private:
    QObject * navigationView_ = nullptr;
    QmlComponentsCache * cache_ = nullptr;

    std::stack<QQuickItem*> pages_;
};


} // namespace Backbone
