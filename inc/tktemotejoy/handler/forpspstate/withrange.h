#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>
#include <utility>

template< typename HANDLER_T >
class WithRangeForPspState final : public Mapping::OperateAxisHandlerForPspState
{
    const HANDLER_T HANDLER;

public:
    WithRangeForPspState(
        const __s16     _MIN
        , const __s16   _MAX
        , const __s16   _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        //TODO
        : HANDLER( std::move( _handler ) )
    {
    }

    void operator()(
        const __s16     _VALUE
        , PspState &    _pspState
    ) const override
    {
        //TODO
        this->HANDLER(
            64
            , _pspState
        );
/*
        if( std::abs( _VALUE ) <= this->DEAD_ZONE ) {
            return;
        }

        this->HANDLER(
            _VALUE
            , _pspState
        );
*/
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H
