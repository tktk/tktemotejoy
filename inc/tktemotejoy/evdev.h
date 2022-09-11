#ifndef TKTEMOTEJOY_EVDEV_H
#define TKTEMOTEJOY_EVDEV_H

#include "tktemotejoy/descriptorcloser.h"
#include <linux/input.h>
#include <bitset>
#include <array>
#include <string>

enum {
    EVDEV_BUTTONS = KEY_MAX,
    EVDEV_AXES = ABS_MAX,

    EVDEV_INPUT_EVENTS_SIZE = 100,
};

using EvdevKeyStates = std::bitset< EVDEV_BUTTONS >;

struct EvdevAbsData
{
    alignas( 1 ) int value;
    alignas( 1 ) int min;
    alignas( 1 ) int max;
    alignas( 1 ) int fuzz;
    alignas( 1 ) int flat;
    alignas( 1 ) int resolution;
};

using EvdevAbsDataArray = std::array<
    EvdevAbsData
    , EVDEV_AXES
>;

using EvdevInputEvents = std::array<
    input_event
    , EVDEV_INPUT_EVENTS_SIZE
>;

DescriptorCloser openEvdev(
    int &
    , const std::string &
);

EvdevKeyStates generateEvdevKeyStates(
    const int
);

EvdevAbsDataArray generateEvdevAbsDataArray(
    const int
);

EvdevInputEvents::size_type readEvdevInputEvents(
    const int
    , EvdevInputEvents &
);

#endif  // TKTEMOTEJOY_EVDEV_H
