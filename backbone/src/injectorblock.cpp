#include <backbone/injectorblock.h>
#include <backbone/incubator.h>
#include <backbone/qmlglobalscope.h>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlComponent>


namespace Backbone {


InjectorBlock::InjectorBlock(QQuickItem * parent)
    : QQuickItem(parent)
{}


void InjectorBlock::setContext(QVariant context)
{
    context_.swap(context);
    emit contextChanged();
}


void InjectorBlock::setViewComponent(QQmlComponent * component)
{
    if (viewComponent_ != component)
    {
        viewComponent_ = component;
        emit viewComponentChanged();
    }
}


void InjectorBlock::componentComplete()
{
    QQuickItem::componentComplete();

    if (!viewComponent_) return;
    Q_ASSERT(!view_);

    // todo: global context
    view_ = qobject_cast<QQuickItem*>(viewComponent_->beginCreate(qmlContext(this)));

    // todo: handle error
    Q_ASSERT(view_);
    {
        const auto engine = qmlEngine(this);
        const auto rootCtx = engine->rootContext();
        const auto globalScope = qobject_cast<QmlGlobalScope*>(rootCtx->contextObject());

        // todo: handle error
        Q_ASSERT(globalScope);

        const auto injector = globalScope->injector();

        // todo: handle error
        injector->inject(view_, context_);
    }

    view_->setParent(this);
    view_->setParentItem(this);

    viewComponent_->completeCreate();
}


} // namespace Backbone
