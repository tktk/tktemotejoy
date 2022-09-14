#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace {
    enum {
        PSP_STATE_AXIS_ZENO = 0x80,
        PSP_STATE_AXIS_MIN = 0x00,
        PSP_STATE_AXIS_MAX = 0xff,
    };
}

PspState::Axis calcPspStateAxis(
    const __s16     _VALUE
    , const __s16   _LIMIT
)
{
    //TODO
    return 0;
/*
    if( _JS_EVENT_AXIS >= _MAX ) {
        return PSP_STATE_AXIS_MAX;
    } else if( _JS_EVENT_AXIS <= -_MAX ) {
        return PSP_STATE_AXIS_MIN;
    }

    return jsEventAxisToPspStateAxis( static_cast< __s16 >( static_cast< int >( _JS_EVENT_AXIS ) * static_cast< int >( JS_EVENT_AXIS_MAX ) / static_cast< int >( _MAX ) ) );
*/
}
