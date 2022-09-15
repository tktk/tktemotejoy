#include "tktemotejoy/generatehandler/operateaxishandlerforpspstate.h"
#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforpspstate.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforpspstate.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

Mapping::OperateAxisHandlerForPspStateUnique generateOperateAxisHandlerForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::OperateAxisHandlerForPspStateUnique();

    handlerUnique = generateToAxisXUnique_new( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToAxisYUnique_new( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToButtonHandlersForPspStateUnique_new( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToButtonHandlerForPspStateUnique_new( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    return handlerUnique;
}
