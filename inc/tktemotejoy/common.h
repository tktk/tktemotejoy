#ifndef TKTEMOTEJOY_COMMON_H
#define TKTEMOTEJOY_COMMON_H

#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

PspState::Axis jsEventAxisToPspStateAxis(
    const __s16
);

#endif  // TKTEMOTEJOY_COMMON_H
