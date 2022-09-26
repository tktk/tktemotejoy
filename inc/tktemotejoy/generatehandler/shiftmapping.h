#ifndef TKTEMOTEJOY_GENERATEHANDLER_SHIFTMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_SHIFTMAPPING_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::PressButtonHandlerForChangeMappingUnique generateShiftMappingUnique(
    const Json::object_t &
    , const MappingNames &
);

#endif  // TKTEMOTEJOY_GENERATEHANDLER_SHIFTMAPPING_H
