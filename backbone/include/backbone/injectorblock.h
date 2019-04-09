#pragma once
#include <QtQuick/QQuickItem>
#include <QtCore/QVariant>


namespace Backbone {


class InjectorBlock
    : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant context READ context WRITE setContext NOTIFY contextChanged FINAL)

    // todo: any type of component
    Q_PROPERTY(QQmlComponent * viewComponent READ viewComponent WRITE setViewComponent NOTIFY viewComponentChanged FINAL)
    Q_PROPERTY(QQuickItem * view READ view NOTIFY viewChanged FINAL)

    Q_CLASSINFO("DefaultProperty", "viewComponent")

public:
    explicit InjectorBlock(QQuickItem * parent = nullptr);

    const QVariant & context() const { return context_; }
    QQmlComponent * viewComponent() const { return viewComponent_; }
    QQuickItem * view() const { return view_; }

    void setContext(QVariant context);
    void setViewComponent(QQmlComponent * component);

    void componentComplete() override;

signals:
    void contextChanged();
    void viewComponentChanged();
    void viewChanged();

private:
    QVariant context_;
    QQmlComponent * viewComponent_ = nullptr;
    QQuickItem * view_ = nullptr;
};


} // namespace Backbone
