#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGEONEWAY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGEONEWAY_H

#include "tktemotejoy/handler/common/withrangeonewayimpl.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

template< typename HANDLER_T >
class WithRangeOneWayForPspState final : public Mapping::OperateAxisHandlerForPspState
{
    const WithRangeOneWayImpl< HANDLER_T >  IMPL;

public:
    WithRangeOneWayForPspState(
        const __s32     _MIN
        , const __s32   _MAX
        , const __s32   _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        : IMPL(
            _MIN
            , _MAX
            , _DEAD_ZONE
            , std::move( _handler )
        )
    {
    }

    void operator()(
        const __s32     _VALUE
        , PspState &    _pspState
    ) const override
    {
        this->IMPL(
            []{}
            , _VALUE
            , _pspState
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGEONEWAY_H
