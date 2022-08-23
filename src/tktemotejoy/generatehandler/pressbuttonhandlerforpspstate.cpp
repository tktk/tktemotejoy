#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/tobuttons.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForPspStateUnique generatePressButtonHandlerForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateToButtonsUnique( _OBJECT );
}
