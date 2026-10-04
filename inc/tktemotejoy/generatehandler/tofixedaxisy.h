#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXISY_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXISY_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

namespace tktemotejoy {
    Mapping::PressButtonHandlerForPspStateUnique generateToFixedAxisYUnique(
        const Json::object_t &
    );
}

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXISY_H
