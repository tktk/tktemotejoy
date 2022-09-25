#ifndef TKTEMOTEJOY_GENERATEHANDLER_OPERATEAXISHANDLERFORCHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_OPERATEAXISHANDLERFORCHANGEMAPPING_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::OperateAxisHandlerForChangeMappingUnique generateOperateAxisHandlerForChangeMappingUnique_new(
    const Json::object_t &
    , const MappingNames &
);

//REMOVEME
Mapping::OperateAxisHandlerForChangeMappingUnique generateOperateAxisHandlerForChangeMappingUnique(
    const Json::object_t &
);

#endif  // TKTEMOTEJOY_GENERATEHANDLER_OPERATEAXISHANDLERFORCHANGEMAPPING_H
