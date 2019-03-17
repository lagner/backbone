#include <QtQuick/QQuickItem>
#include <QtQml/QQmlComponent>
#include "fwd.h"


namespace Backbone {


class DelegateBuilder
    : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlComponent * delegate READ delegate WRITE setDelegate NOTIFY delegateChanged FINAL)
    Q_PROPERTY(QVariant context READ context WRITE setContext NOTIFY contextChanged FINAL)

public:
    explicit DelegateBuilder(QQuickItem * parent = nullptr);

    void componentComplete() override;

    QQmlComponent * delegate() const { return delegate_; }
    void setDelegate(QQmlComponent * delegate);

    QVariant context() const { return context_; }
    void setContext(QVariant ctx);

signals:
    void delegateChanged();
    void contextChanged();

private:
    void buildView();

private:
    QQmlComponent * delegate_ = nullptr;
    QVariant context_;
};

} // namespace Backbone
