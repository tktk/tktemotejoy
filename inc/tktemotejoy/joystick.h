#ifndef TKTEMOTEJOY_JOYSTICK_H
#define TKTEMOTEJOY_JOYSTICK_H

#include "tktemotejoy/descriptorcloser.h"
#include <linux/joystick.h>
#include <string>

DescriptorCloser openJoystick(
    int &
    , const std::string &
);

unsigned char getJoystickButtons(
    const int
);

unsigned char getJoystickAxes(
    const int
);

void readJoystick(
    const int
    , js_event &
);

#endif  // TKTEMOTEJOY_JOYSTICK_H
