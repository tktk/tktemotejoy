#include "tktemotejoy/generatehandler/tobuttons.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForPspStateUnique generateToButtonsUnique(
    const Json::object_t &  _OBJECT
)
{
    //TODO
    return Mapping::handlerUnique( static_cast< ToButtons * >( nullptr ) );
}
