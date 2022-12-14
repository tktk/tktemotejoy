#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H

#include "tktemotejoy/handler/common/withrangeimpl.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

template< typename HANDLER_T >
class WithRangeForPspState final : public Mapping::OperateAxisHandlerForPspState
{
    const WithRangeImpl< HANDLER_T >    IMPL;

public:
    WithRangeForPspState(
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

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H
