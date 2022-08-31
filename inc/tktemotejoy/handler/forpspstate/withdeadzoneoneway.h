#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONEONEWAY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONEONEWAY_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>
#include <utility>

template< typename HANDLER_T >
class WithDeadZoneOneWayForPspState final : public Mapping::OperateAxisHandlerForPspState
{
    const __s16 DEAD_ZONE;

    const HANDLER_T HANDLER;

public:
    WithDeadZoneOneWayForPspState(
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
        if( _VALUE <= this->DEAD_ZONE ) {
            return;
        }

        this->HANDLER(
            _VALUE
            , _pspState
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONEONEWAY_H
