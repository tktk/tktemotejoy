#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXISX_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXISX_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

namespace tktemotejoy {
    Mapping::PressButtonHandlerForPspStateUnique generateToFixedAxisXUnique(
        const Json::object_t &
    );
}

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXISX_H
