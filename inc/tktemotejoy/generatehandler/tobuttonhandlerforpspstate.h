#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERFORPSPSTATE_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERFORPSPSTATE_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

namespace tktemotejoy {
    Mapping::OperateAxisHandlerForPspStateUnique generateToButtonHandlerForPspStateUnique(
        const Json::object_t &
    );
}

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERFORPSPSTATE_H
