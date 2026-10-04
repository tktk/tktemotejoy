#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONS_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"

namespace tktemotejoy {
    Mapping::PressButtonHandlerForPspStateUnique generateToButtonsUnique(
        const Json::object_t &
    );
}

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONS_H
