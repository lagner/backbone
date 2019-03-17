#include <backbone/pagepresenter.h>
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlProperty>



namespace Backbone {


PagePresenter::PagePresenter(QObject * parent)
    : Presenter(parent)
{
}


void PagePresenter::onCreate(QQuickItem * view, const QVariantMap &)
{
    QQmlProperty stackViewProperty(view, "StackView.view", qmlContext(view));
    auto stackView = stackViewProperty.read().value<QObject*>();

    qDebug() << "onCreate: stackView " << !!stackView;
}


void PagePresenter::activating()
{
//    qDebug() << objectName() << " activating";
}

void PagePresenter::activated()
{
//    qDebug() << objectName() << " activated";
}

void PagePresenter::deactivating()
{
//    qDebug() << objectName() << " deactivating";
}

void PagePresenter::deactivated()
{
//    qDebug() << objectName() << " deactivated";
}


void PagePresenter::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
    case Qt::Key_Back:
        qDebug() << "key back pressed";
        return;
        // fixme: go back from page
        /*
        if (router->depth() == 1)
        {
            qApp->quit();
        }
        else
        {
            router->pop();
        }
        return;
         */
    }
}


} // namespace Backbone
