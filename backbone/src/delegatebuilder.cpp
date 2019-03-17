#include <backbone/delegatebuilder.h>
#include <backbone/qmlglobalscope.h>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>


namespace Backbone {


DelegateBuilder::DelegateBuilder(QQuickItem * parent)
    : QQuickItem (parent)
{}


void DelegateBuilder::componentComplete()
{
    QQuickItem::componentComplete();
    buildView();
}


void DelegateBuilder::setDelegate(QQmlComponent * delegate)
{
    if (delegate_ != delegate)
    {
        delegate_ = delegate;
        emit delegateChanged();
    }
}


void DelegateBuilder::setContext(QVariant ctx)
{
    context_.swap(ctx);
    emit contextChanged();
}


void DelegateBuilder::buildView()
{
    if (!delegate_) {
        return;
    }
    // create routed item
    auto engine = qmlEngine(this);
    Q_ASSERT(engine);
    auto ctx = engine->rootContext();
    Q_ASSERT(ctx);
    auto scope = qobject_cast<QmlGlobalScope*>(ctx->contextObject());
    Q_ASSERT(scope);

    auto injector_ = scope->injector();
    Q_ASSERT(injector_);

    auto object = delegate_->beginCreate(qmlContext(this));
    // todo: scope guard

    if (auto item = qobject_cast<QQuickItem*>(object))
    {
        item->setParent(this);
        item->setParentItem(this);
    }

    // todo: handle error
    injector_->inject(object, context_);

    delegate_->completeCreate();
}


} // namespace Backbone
