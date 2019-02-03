#pragma once
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlComponent>
#include "pagepresenter.h"
#include "container.h"


namespace Backbone {


class Page
    : public Container
{
    Q_OBJECT
    Q_PROPERTY(QQmlComponent * viewDelegate READ viewDelegate WRITE setViewDelegate NOTIFY viewDelegateChanged FINAL)
    Q_PROPERTY(QQuickItem * view READ view NOTIFY viewChanged FINAL)
    Q_PROPERTY(Backbone::PagePresenter * presenter READ presenter NOTIFY presenterChanged FINAL)

    Q_CLASSINFO("DefaultProperty", "viewDelegate")

    // TODO: property for incoming arguments
    // or ... context?

public:
    Page();
    ~Page();

    void classBegin() override;
    void componentComplete() override;
    void keyPressEvent(QKeyEvent * event) override;

    QQmlComponent * viewDelegate() const { return delegate_; }
    QQuickItem * view() const { return view_; }
    Backbone::PagePresenter * presenter() const { return presenter_; }

    void setViewDelegate(QQmlComponent * delegate);

signals:
    void viewDelegateChanged();
    void viewChanged();
    void presenterChanged();

private:
    void subscribe();

private:
    QQmlComponent * delegate_ = nullptr;
    QQuickItem * view_ = nullptr;
    PagePresenter * presenter_ = nullptr;
};


} // namespace Backbone
