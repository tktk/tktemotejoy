#ifndef TKTEMOTEJOY_GENERATEHANDLER_PRESSBUTTONHANDLERFORCHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_PRESSBUTTONHANDLERFORCHANGEMAPPING_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForChangeMappingUnique generatePressButtonHandlerForChangeMappingUnique_new(
    const Json::object_t &
    , const MappingNames &
);

//REMOVEME
Mapping::PressButtonHandlerForChangeMappingUnique generatePressButtonHandlerForChangeMappingUnique(
    const Json::object_t &
);

#endif  // TKTEMOTEJOY_GENERATEHANDLER_PRESSBUTTONHANDLERFORCHANGEMAPPING_H
