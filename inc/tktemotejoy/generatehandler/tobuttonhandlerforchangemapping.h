#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERFORCHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERFORCHANGEMAPPING_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlerForChangeMappingUnique_new(
    const Json::object_t &
    , const MappingNames &
);

//REMOVEME
Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlerForChangeMappingUnique(
    const Json::object_t &
);

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERFORCHANGEMAPPING_H
