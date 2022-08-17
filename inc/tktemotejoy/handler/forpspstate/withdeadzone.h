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
        , ARGS_T ...    _args
    )
        : DEAD_ZONE( 0 )
        , HANDLER( _args ... )
    {
        //TODO
    }

    void operator()(
        const __s16
        , PspState &
    ) const override
    {
        //TODO
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHDEADZONE_H
