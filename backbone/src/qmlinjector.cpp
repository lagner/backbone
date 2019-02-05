#include <backbone/qmlinjector.h>
#include <QtCore/QStringList>
#include <QtQml/QQmlProperty>


namespace Backbone {


bool QmlInjector::inject(QObject * object, const QStringList & properties) const
{
    Q_ASSERT(object);
    Q_ASSERT(!properties.empty());

    bool result = true;

    for (const auto & propertyName : properties)
    {
        if (!inject(object, propertyName))
        {
            result = false;
        }
    }
    return result;
}


QObject * QmlInjector::inject(QObject *object, const QString & propertyName) const
{
    QQmlProperty property(object, propertyName);

    if (!property.isValid() || !property.isWritable())
    {
        qWarning("%s does not have %s property",
             object->metaObject()->className(),
             qPrintable(propertyName));
        return nullptr;
    }

    auto typeName = property.propertyTypeName();
    auto it = creators_.find(typeName);
    if (it == creators_.cend())
    {
        qWarning("there is no factory for %s", qPrintable(typeName));
        return nullptr;
    }

    auto instance = (it->second)();
    instance->setParent(object);

    if (!property.write(QVariant::fromValue(instance)))
    {
        qWarning("Value of property %s can't be set", qPrintable(typeName));
        return nullptr;
    }

    return instance;
}


} // namespace Backbone
