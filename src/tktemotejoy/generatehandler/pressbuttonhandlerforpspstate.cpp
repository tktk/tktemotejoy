#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/tobuttons.h"
#include "tktemotejoy/generatehandler/tofixedaxisx.h"
#include "tktemotejoy/generatehandler/tofixedaxisy.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForPspStateUnique generatePressButtonHandlerForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::PressButtonHandlerForPspStateUnique();

    handlerUnique = generateToButtonsUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToFixedAxisXUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToFixedAxisYUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    return Mapping::PressButtonHandlerForPspStateUnique();  //TODO 例外投げる
}
