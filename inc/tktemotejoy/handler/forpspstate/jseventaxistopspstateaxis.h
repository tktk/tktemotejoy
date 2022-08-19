#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_JSEVENTAXISTOPSPSTATEAXIS_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_JSEVENTAXISTOPSPSTATEAXIS_H

#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

PspState::Axis jsEventAxisToPspStateAxis(
    const __s16
);

PspState::Axis jsEventAxisToPspStateAxis(
    const __s16
    , const __s16
);

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_JSEVENTAXISTOPSPSTATEAXIS_H
