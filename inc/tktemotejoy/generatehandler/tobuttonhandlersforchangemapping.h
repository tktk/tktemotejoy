#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERSFORCHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERSFORCHANGEMAPPING_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlersForChangeMappingUnique_new(
    const Json::object_t &
    , const MappingNames &
);

//REMOVEME
Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlersForChangeMappingUnique(
    const Json::object_t &
);

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERSFORCHANGEMAPPING_H
