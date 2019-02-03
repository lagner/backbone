#include <backbone/appcontroller.h>
#include <backbone/qmlglobalscope.h>
#include <backbone/page.h>
#include <QtCore/QDebug>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlProperty>
#include <QtQuick/QQuickItem>


namespace Backbone {


Page::Page()
{
    setFlags(ItemIsFocusScope | ItemAcceptsInputMethod);
}


Page::~Page()
{
    qDebug() << "-- Page dies";
}


void Page::classBegin()
{
    Container::classBegin();

    QQmlProperty presenterProperty(this, QStringLiteral("presenter"));
    qDebug() << "presenter property typename: " << presenterProperty.propertyTypeName();
    qDebug() << "is writable: " << presenterProperty.isWritable();
    qDebug() << "is valid: " << presenterProperty.isValid();
}


void Page::componentComplete()
{
    Container::componentComplete();

    QQmlEngine * engine = qmlEngine(this);
    Q_ASSERT(engine);

    QQmlContext * rootContext = engine->rootContext();
    Q_ASSERT(rootContext);

    QmlGlobalScope * scope = qobject_cast<QmlGlobalScope*>(rootContext->contextObject());
    Q_ASSERT(scope);

    AppController * controller = scope->appController();
    Q_ASSERT(controller);

    Q_ASSERT(delegate_);

    view_ = qobject_cast<QQuickItem*>(delegate_->beginCreate(rootContext));
    Q_ASSERT(view_);
    view_->setParent(this);
    view_->setParentItem(this);

    QQmlProperty presenterProperty(view_, QStringLiteral("presenter"));

    QString name = QString::fromLatin1(presenterProperty.propertyTypeName());
    presenter_ = controller->resolvePresenter(name);
    if (presenter_)
    {
        presenter_->setParent(this);
        presenter_->setRouter(scope->router());
        presenter_->onCreate(view_, std::move(args_));

        QVariant ptr = QVariant::fromValue(presenter_);

        if (!presenterProperty.write(ptr))
        {
            qDebug() << "set property failed";
        }

        subscribe();
    }
    else
    {
        qDebug() << name
                 << " - presenter was not found";
    }
    delegate_->completeCreate();
}


void Page::keyPressEvent(QKeyEvent * event)
{
    if (presenter_)
    {
        presenter_->keyPressEvent(event);
    }
}


void Page::setViewDelegate(QQmlComponent * viewDelegate)
{
    if (delegate_ != viewDelegate)
    {
        delegate_ = viewDelegate;
        emit viewDelegateChanged();
    }
}


void Page::subscribe()
{
#if defined(STACK_VIEW_ENABLE)
    QQmlEngine * engine = qmlEngine(this);
    Q_ASSERT(engine);

    auto attached = qmlAttachedPropertiesObject<QQuickStackView>(this, true);

    QQuickStackViewAttached * proxy = qobject_cast<QQuickStackViewAttached*>(attached);

    if (!proxy)
    {
        qDebug() << "invalid attached type";
        return;
    }

    connect(proxy, &QQuickStackViewAttached::activating, this, [this] {
        setFocus(true, Qt::FocusReason::OtherFocusReason);
    });
    connect(proxy, &QQuickStackViewAttached::removed, this, [this] {
        deleteLater();
    });

    // TODO: hold connections
    connect(
        proxy, &QQuickStackViewAttached::activating,
        presenter_, &PagePresenter::activating);
    connect(
        proxy, &QQuickStackViewAttached::activated,
        presenter_, &PagePresenter::activated);
    connect(
        proxy, &QQuickStackViewAttached::deactivating,
        presenter_, &PagePresenter::deactivating);
    connect(
        proxy, &QQuickStackViewAttached::deactivated,
        presenter_, &PagePresenter::deactivated);
#endif
}


/*
void Page::setArgs(ArgsWeakWrapper wrapper)
{
    if (ArgsPtr ptr = wrapper.args.lock())
    {
        args_.swap(ptr->members);

        for (auto it = args_.cbegin(); it != args_.cend(); ++it)
        {
            qDebug() << " args - " << it.key();
        }
    }
    else
    {
        qWarning() << "args already died";
    }
}
*/


} // namespace Backbone
