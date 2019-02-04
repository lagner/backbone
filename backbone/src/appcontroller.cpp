#include <backbone/appcontroller.h>
#include <backbone/executors.h>
#include <backbone/pagepresenter.h>
#include <QtCore/QDebug>
#include <QtQml/QJSValue>
#include <QtQml/QQmlComponent>
#include <portable_concurrency/future>


namespace Backbone {


AppController::AppController(QObject * parent)
    : QObject(parent)
{}


} // namespace Backbone
