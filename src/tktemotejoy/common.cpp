#include "tktemotejoy/common.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    enum {
        JS_EVENT_AXIS_ZERO = 0x8000,
        SHIFT_TO_PSP_STATE_AXIS = 8,
    };
}

PspState::Axis jsEventAxisToPspStateAxis(
    const __s16 _JS_EVENT_AXIS
)
{
    return ( _JS_EVENT_AXIS + JS_EVENT_AXIS_ZERO ) >> SHIFT_TO_PSP_STATE_AXIS;
}

PspState::Axis jsEventAxisToPspStateAxis(
    const __s16     _JS_EVENT_AXIS
    , const __s16   _MAX
)
{
    //TODO
    return 0xff;
}
