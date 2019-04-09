#pragma once
#include <QtCore/QObject>
#include <backbone/pagepresenter.h>
#include <backbone/injector.h>
#include <QtQml/QJSValue>
#include "global.h"
#include "fwd.h"


namespace Backbone {


class AppController
    : public QObject
{
    Q_OBJECT
public:
    AppController(QObject * parent);

private:
};


} // namespace Backbone
