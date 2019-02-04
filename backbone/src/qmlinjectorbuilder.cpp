#include <backbone/qmlinjectorbuilder.h>
#include <backbone/qmlinjector.h>


namespace Backbone {


QmlInjectorBuilder::QmlInjectorBuilder(char const * const ns)
    : qmlNamespace_(ns)
{
}


QmlInjectorPtr QmlInjectorBuilder::build()
{
    return std::make_shared<QmlInjector>(std::move(items_));
}


} // namespace Backbone
