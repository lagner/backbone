#include <backbone/injectorbuilder.h>
#include <backbone/injector.h>
#include <portable_concurrency/functional>


namespace Backbone {


InjectorBuilder::InjectorBuilder(char const * const ns)
    : qmlNamespace_(ns)
{
}


InjectorPtr InjectorBuilder::build()
{
    std::vector<std::pair<InjectorTypeId, InjectorFactory>> creators;
    creators.reserve(items_.size());

    for (auto & it : items_)
    {
        creators.emplace_back(std::move(it.first), std::move(it.second));
    }
    items_.clear();

    return std::make_shared<Injector>(std::move(creators));
}


} // namespace Backbone
