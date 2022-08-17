#include "tktemotejoy/common.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    enum {
        JS_EVENT_AXIS_TO_PSP_STATE_AXIS = 0x8000,
        SHIFT_TO_PSP_STATE_AXIS = 8,

        PSP_STATE_AXIS_MAX = 0xff,
        PSP_STATE_AXIS_MIN = 0x00,
        JS_EVENT_AXIS_MAX = 0x7fff,
    };
}

PspState::Axis jsEventAxisToPspStateAxis(
    const __s16 _JS_EVENT_AXIS
)
{
    return ( _JS_EVENT_AXIS + JS_EVENT_AXIS_TO_PSP_STATE_AXIS ) >> SHIFT_TO_PSP_STATE_AXIS;
}

PspState::Axis jsEventAxisToPspStateAxis(
    const __s16     _JS_EVENT_AXIS
    , const __s16   _MAX
)
{
    if( _JS_EVENT_AXIS >= _MAX ) {
        return PSP_STATE_AXIS_MAX;
    }

    return jsEventAxisToPspStateAxis( static_cast< __s16 >( static_cast< int >( _JS_EVENT_AXIS ) * static_cast< int >( JS_EVENT_AXIS_MAX ) / static_cast< int >( _MAX ) ) );
}
