#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOGGLEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOGGLEMAPPING_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForChangeMappingUnique generateToggleMappingUnique_new(
    const Json::object_t &
    , const MappingNames &
);

//REMOVEME
Mapping::PressButtonHandlerForChangeMappingUnique generateToggleMappingUnique(
    const Json::object_t &
);

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOGGLEMAPPING_H
