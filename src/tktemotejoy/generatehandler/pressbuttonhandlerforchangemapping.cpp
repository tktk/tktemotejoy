#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/generatehandler/togglemapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForChangeMappingUnique generatePressButtonHandlerForChangeMappingUnique_new(
    const Json::object_t &  _OBJECT
    , const MappingNames &  _MAPPING_NAMES
)
{
    //TODO
    return Mapping::PressButtonHandlerForChangeMappingUnique();
}

//REMOVEME
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
