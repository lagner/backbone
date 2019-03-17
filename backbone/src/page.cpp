#include <backbone/appcontroller.h>
#include <backbone/qmlglobalscope.h>
#include <backbone/page.h>
#include <backbone/pagepresenter.h>
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
}


void Page::classBegin()
{
    QQuickItem::classBegin();
}


void Page::componentComplete()
{
    QQuickItem::componentComplete();
}


void Page::keyPressEvent(QKeyEvent * event)
{
    if (presenter_)
    {
        presenter_->keyPressEvent(event);
    }
}

void Page::setPagePresenter(PagePresenter * presenter)
{
    presenter_ = presenter;
}


} // namespace Backbone
