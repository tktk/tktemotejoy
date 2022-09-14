//REMOVEME
#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONE_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONE_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>
#include <cmath>
#include <utility>

template< typename HANDLER_T >
class WithDeadZoneForPspState final : public Mapping::OperateAxisHandlerForPspState
{
    const __s16 DEAD_ZONE;

    const HANDLER_T HANDLER;

public:
    WithDeadZoneForPspState(
        const __s16     _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        : DEAD_ZONE( _DEAD_ZONE )
        , HANDLER( std::move( _handler ) )
    {
    }

    void operator()(
        const __s16     _VALUE
        , PspState &    _pspState
    ) const override
    {
        if( std::abs( _VALUE ) <= this->DEAD_ZONE ) {
            return;
        }

        this->HANDLER(
            _VALUE
            , _pspState
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONE_H
