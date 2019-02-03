#include <backbone/block.h>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlProperty>
#include <QtCore/QDebug>


namespace Backbone {


bool Block::autoload() const
{
    return autoload_;
}


void Block::setAutoload(bool autoload)
{
    if (autoload_ != autoload)
    {
        autoload_ = autoload;
        emit autoloadChanged();
    }
}


void Block::classBegin()
{
    Container::classBegin();

    QQmlProperty presenterProperty(this, QStringLiteral("presenter"));
}


void Block::componentComplete()
{
    Container::componentComplete();

    // TODO: get page
    // TODO: get PagePresenter

    QQmlEngine * engine = qmlEngine(this);
    Q_UNUSED(engine);


    QQmlProperty presenterProperty(this, QStringLiteral("presenter"));
}



} // namespace Backbone
