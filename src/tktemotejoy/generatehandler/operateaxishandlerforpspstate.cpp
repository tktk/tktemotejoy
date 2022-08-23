#include "tktemotejoy/generatehandler/operateaxishandlerforpspstate.h"
#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <stdexcept>

Mapping::OperateAxisHandlerForPspStateUnique generateOperateAxisHandlerForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::OperateAxisHandlerForPspStateUnique();

    handlerUnique = generateToAxisXUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToAxisYUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    return Mapping::OperateAxisHandlerForPspStateUnique();
}
