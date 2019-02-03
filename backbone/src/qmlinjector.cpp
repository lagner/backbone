#include <backbone/qmlinjector.h>
#include <backbone/pagepresenter.h>
#include <QtQml/QQmlProperty>


namespace Backbone {


QObject * QmlInjector::create(std::string name) const
{
    auto it = creators_.find(name);
    if (it != creators_.end())
    {
        if (auto ptr = it->second())
        {
            ptr->setObjectName(QString::fromStdString(name));
            return ptr;
        }
    }
    return nullptr;
}


PagePresenter * QmlInjector::injectPresenter(QObject * object) const
{
    inject(object, QStringList() << "presenter");

    QQmlProperty property(object, "presenter");
    return property.read().value<PagePresenter*>();
}


bool QmlInjector::inject(QObject * object, const QStringList & properties) const
{
    Q_ASSERT(object);
    Q_ASSERT(!properties.empty());

    bool result = true;

    for (const auto & propertyName : properties)
    {
        QQmlProperty property(object, propertyName);

        if (!property.isValid() || !property.isWritable())
        {
            result = false;
            qWarning("%s does not have %s property",
                object->metaObject()->className(),
                qPrintable(propertyName));
            continue;
        }

        auto typeName = property.propertyTypeName();
        auto it = creators_.find(typeName);
        if (it == creators_.cend())
        {
            result = false;
            qWarning("there is no factory for %s", qPrintable(typeName));
            continue;
        }

        auto instance = (it->second)();
        instance->setParent(object);

        if (!property.write(QVariant::fromValue(instance)))
        {
            qWarning("Value of property %s can't be set", qPrintable(typeName));
            result = false;
        }
    }
    return result;
}


} // namespace Backbone
