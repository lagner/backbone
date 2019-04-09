#pragma once
#include <QtCore/QObject>


namespace Backbone {


class Scope
    : public QObject
{
    Q_OBJECT

public:
    Scope(QObject * parent);

private:
};


} // namespace Backbone
