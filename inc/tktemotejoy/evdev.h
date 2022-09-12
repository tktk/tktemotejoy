#ifndef TKTEMOTEJOY_EVDEV_H
#define TKTEMOTEJOY_EVDEV_H

#include "tktemotejoy/descriptorcloser.h"
#include <linux/input.h>
#include <bitset>
#include <array>
#include <string>

enum {
    EVDEV_INPUT_EVENTS_SIZE = 100,
};

using EvdevKeyIndices = std::array<
    int
    , KEY_MAX
>;

using EvdevAbsIndices = std::array<
    int
    , ABS_MAX
>;

using EvdevKeyStates = std::bitset< KEY_MAX >;

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
    , ABS_MAX
>;

using EvdevInputEvents = std::array<
    input_event
    , EVDEV_INPUT_EVENTS_SIZE
>;

DescriptorCloser openEvdev(
    int &
    , const std::string &
);

EvdevKeyIndices generateEvdevKeyIndices(
    const int
);

EvdevAbsIndices generateEvdevAbsIndices(
    const int
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
