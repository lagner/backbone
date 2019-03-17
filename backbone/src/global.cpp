#include <backbone/appcontroller.h>
#include <backbone/block.h>
#include <backbone/global.h>
#include <backbone/page.h>
#include <backbone/pagepresenter.h>
#include <backbone/delegatebuilder.h>
#include <QtQml/qqml.h>

namespace {

const char * const NS = "Backbone";

} // namespace


namespace Backbone
{


void import()
{
    // @uri Backbone
    qmlRegisterUncreatableType<AppController>(NS, 1, 0, "AppController", "impossible");
    qmlRegisterType<Block>(NS, 1, 0, "Block");
    qmlRegisterType<Page>(NS, 1, 0, "Page");
    qmlRegisterType<PagePresenter>(NS, 1, 0, "PagePresenter");
    qmlRegisterType<DelegateBuilder>(NS, 1, 0, "DelegateBuilder");
}


} // namespace Backbone
