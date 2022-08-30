#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/generatehandler/togglemapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForChangeMappingUnique generatePressButtonHandlerForChangeMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::PressButtonHandlerForChangeMappingUnique();

    handlerUnique = generateShiftMappingUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToggleMappingUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    return handlerUnique;
}
