#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace {
    enum {
        PSP_STATE_AXIS_ZERO = 0x80,
        PSP_STATE_AXIS_MIN = 0x00,
        PSP_STATE_AXIS_MAX = 0xff,
    };
}

PspState::Axis calcPspStateAxis(
    const __s16     _VALUE
    , const __s16   _LIMIT
)
{
    if( _VALUE >= _LIMIT ) {
        return PSP_STATE_AXIS_MAX;
    } else if( _VALUE <= -_LIMIT ) {
        return PSP_STATE_AXIS_MIN;
    }

    return PSP_STATE_AXIS_ZERO + ( _VALUE * PSP_STATE_AXIS_ZERO / _LIMIT );
}
