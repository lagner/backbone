#pragma once
#include <backbone/pagepresenter.h>
#include <usecases/usersearchusecase.h>


class IndexPagePresenter
    : public Backbone::PagePresenter
{
    Q_OBJECT
public:
    IndexPagePresenter(QObject * parent = nullptr);

    void onCreate(QQuickItem * view, const QVariantMap & args) override;

public slots:
    void searchByText(QString pattern);
    void collect();

private slots:
    void onDataReady();

private:
    UserSearchUsecasePtr usecase_;
};
