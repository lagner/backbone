#include "indexpagepresenter.h"
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickItem>
#include <usecases/usersearchusecase.h>


IndexPagePresenter::IndexPagePresenter(QObject * parent)
    : Backbone::PagePresenter(parent)
{
    usecase_ = std::make_shared<UserSearchUsecase>();

    setObjectName(QStringLiteral("IndexPagePresenter object"));
}


void IndexPagePresenter::onCreate(QQuickItem * view, const QVariantMap & args)
{
    PagePresenter::onCreate(view, args);

    engine_ = QtQml::qmlEngine(view);
}


void IndexPagePresenter::onDataReady()
{
    // data ready push next page

    QVariantMap args;
    args["objectContext"] = QString("context sharedPtr");

    if (!router)
    {
        qDebug() << "no router!";
        return;
    }

    router->push("qrc:///qml/search.qml", std::move(args));
}


void IndexPagePresenter::searchByText(QString pattern)
{
    Q_UNUSED(pattern);

    if (!router || !usecase_)
    {
        qWarning("route or usecase is not defined");
        return;
    }

    usecase_->search(pattern);

    QVariantMap args;
    args.insert(QStringLiteral("pattern"), std::move(pattern));
    args.insert(QStringLiteral("usecase"), QVariant::fromValue(usecase_));

    router->push("qrc:///qml/search.qml", std::move(args));
}


void IndexPagePresenter::collect()
{
    if (engine_)
    {
        engine_->collectGarbage();
    }
}

