#pragma once
#include <backbone/pagepresenter.h>
#include <entities/corecontext.h>


class DetailPagePresenter
    : public Backbone::PagePresenter
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged FINAL)

public:
    DetailPagePresenter();

    void onCreate(QQuickItem * view, const QVariantMap & args) override;

    QObject * model() const { return model_; }

signals:
    void modelChanged();

private:
    QObject * model_ = nullptr;
    ContextPtr context_;
};
