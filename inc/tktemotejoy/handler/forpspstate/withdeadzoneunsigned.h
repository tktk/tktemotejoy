#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONEUNSIGNED_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONEUNSIGNED_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>
#include <utility>

template< typename HANDLER_T >
class WithDeadZoneUnsignedForPspState final : public Mapping::OperateAxisHandlerForPspState
{
    const __u16 DEAD_ZONE;

    const HANDLER_T HANDLER;

public:
    WithDeadZoneUnsignedForPspState(
        const __u16     _DEAD_ZONE
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
        const auto &    VALUE = static_cast< const __u16 & >( _VALUE );

        if( VALUE <= this->DEAD_ZONE ) {
            return;
        }

        this->HANDLER(
            VALUE
            , _pspState
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHDEADZONEUNSIGNED_H
