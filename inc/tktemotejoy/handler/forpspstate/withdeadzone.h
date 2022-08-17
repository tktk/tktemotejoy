#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHDEADZONE_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHDEADZONE_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

template< typename HANDLER_T >
class WithDeadZone final : public Mapping::OperateAxisHandlerForPspState
{
    const __s16 DEAD_ZONE;

    const HANDLER_T HANDLER;

public:
    template< typename ... ARGS_T >
    WithDeadZone(
        const __s16     _DEAD_ZONE
        , ARGS_T & ...  _args
    )
        : DEAD_ZONE( _DEAD_ZONE )
        , HANDLER( _args ... )
    {
    }

    void operator()(
        const __s16     _VALUE
        , PspState &    _pspState
    ) const override
    {
        if( _VALUE <= this->DEAD_ZONE ) {
            return;
        }

        this->HANDLER(
            _VALUE
            , _pspState
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHDEADZONE_H
