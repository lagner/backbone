#include <entities/corecontext.h>
#include "searchpagepresenter.h"

#include "consts.h"


SearchPagePresenter::SearchPagePresenter()
{
    for (int i = 30; i > 0; --i)
    {
        collection_.append(new Branch());
    }
}


QList<QObject*> SearchPagePresenter::model() const
{
    return collection_;
}


void SearchPagePresenter::onCreate(QQuickItem * view, const QVariantMap & args)
{
    Q_UNUSED(view);

    searchUsecase_ = args[QStringLiteral("usecase")].value<UserSearchUsecasePtr>();
}


void SearchPagePresenter::selectItem(int index)
{
    if (index >= collection_.size())
        return;

//    if (!router)
//        return;
//
//    auto item = collection_[index];
//
//    auto ctx = std::make_shared<CoreContext>();
//    ctx->id = QString::number(static_cast<Branch*>(item)->id());
//
//    QVariantMap args;
//    args.insert(QStringLiteral("selectedItem"), QVariant::fromValue(item));
//    args.insert(QStringLiteral("selectedIndex"), QVariant(index));
//    args.insert(Consts::CORE_CONTEXT, QVariant::fromValue(ctx));
//
//    router->push("qrc:///qml/detail.qml", std::move(args));
}
