#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERSFORPSPSTATE_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERSFORPSPSTATE_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

Mapping::OperateAxisHandlerForPspStateUnique generateToButtonHandlersForPspStateUnique_new(
    const Json::object_t &
);

//REMOVEME
Mapping::OperateAxisHandlerForPspStateUnique generateToButtonHandlersForPspStateUnique(
    const Json::object_t &
);

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERSFORPSPSTATE_H
