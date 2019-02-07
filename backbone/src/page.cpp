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
}


void Page::classBegin()
{
    QQuickItem::classBegin();
}


void Page::componentComplete()
{
    QQuickItem::componentComplete();
}


void Page::keyPressEvent(QKeyEvent * )
{
}


} // namespace Backbone
