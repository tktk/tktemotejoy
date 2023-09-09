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
    const __s32     _VALUE
    , const __s32   _LIMIT
    , const __s32   _ERASE_DEAD_ZONE
)
{
    if( _VALUE >= _LIMIT ) {
        return PSP_STATE_AXIS_MAX;
    } else if( _VALUE <= -_LIMIT ) {
        return PSP_STATE_AXIS_MIN;
    }

    const auto  DIRECTION = ( _VALUE >= 0 ) ? 1 : -1;

    return PSP_STATE_AXIS_ZERO + _ERASE_DEAD_ZONE * DIRECTION + ( _VALUE * ( PSP_STATE_AXIS_ZERO - _ERASE_DEAD_ZONE ) / _LIMIT );
}
