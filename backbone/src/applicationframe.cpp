#include <backbone/applicationframe.h>
#include <QtCore/QtDebug>


namespace Backbone {

ApplicationFrame::ApplicationFrame()
{
}


void ApplicationFrame::start()
{
    qDebug() << "application start";

    if (!navigationView_) {
        qDebug() << "there is not navigation view";
        return;
    }
}


} // namespace Backbone
