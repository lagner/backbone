#include <portable_concurrency/functional>
#include <backbone/injector.h>
#include <QtCore/QStringList>
#include <QtQml/QQmlProperty>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QDebug>

using Candidate = std::pair<Backbone::InjectorTypeId, Backbone::InjectorFactory>;
using Factories = std::vector<Candidate>;

namespace  {

Factories::const_iterator search(const Factories & factories, /* string_view */ const char * name)
{
    Q_ASSERT(name);

    auto it = std::lower_bound(
        factories.cbegin(),
        factories.cend(),
        name,
        [] (const Candidate & candidate, const char * id) {
            return candidate.first.compare(id) < 0;
        });

    return (it != factories.cend() && 0 == it->first.compare(name))
        ? it
        : factories.cend();
}

} // namespace


namespace Backbone {


bool Injector::inject(QObject * object, InjectorContextProvider provider) const
{
    if (!object) {
        return false;
    }

    const auto meta = object->metaObject();
    Q_ASSERT(meta);

    bool res = true;

    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
    {
        const auto & property = meta->property(i);
        if (const char * name = property.name())
        {
            if (*name != '$') continue;

            auto it = search(creators_, property.typeName());
            if (it == creators_.cend())
            {
                qWarning()
                    << "there is no factory to create " << property.typeName()
                    << " for " << property.name();
                res = false;
                continue;
            }

            auto instance = (it->second)(provider(it->first));
            if (!instance)
            {
                qWarning()
                    << "factory " << property.typeName() << ", returned nullptr"
                    << " for " << property.name();
                res = false;
                continue;
            }

            if (!property.write(object, QVariant::fromValue(instance.get())))
            {
                qWarning()
                    << "could not inject: " << property.typeName()
                    << " to " << property.name();
                res = false;
                continue;
            }

            instance.release()->setParent(object);
        }
    }
    return res;
}


bool Injector::inject(QObject * object, const QVariant & context) const
{
    return inject(object, [&context] (auto) {
        return context;
    });
}


} // namespace Backbone
