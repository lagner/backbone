#pragma once
#include <QtCore/QObject>
#include "presenter.h"
#include "fwd.h"


namespace Backbone {


class PagePresenter
    : public Presenter
{
    Q_OBJECT
public:
    explicit PagePresenter(QObject * parent = nullptr);

    // presenter entry point
    virtual void onCreate(QQuickItem * view, const QVariantMap & args);

    virtual void activating();
    virtual void activated();
    virtual void deactivating();
    virtual void deactivated();

public slots:
    void keyPressEvent(QKeyEvent * event) override;

protected:

private:
};


} // namespace Backbone


Q_DECLARE_METATYPE(Backbone::PagePresenter*)
