#ifndef TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEONEWAYIMPL_H
#define TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEONEWAYIMPL_H

#include "tktemotejoy/handler/common/calcrangedirection.h"
#include <linux/input.h>
#include <utility>

template< typename HANDLER_T >
class WithRangeOneWayImpl final
{
    const __s32 MIN;
    const __s32 DIRECTION;
    const __s32 DEAD_ZONE;

    const HANDLER_T HANDLER;

public:
    WithRangeOneWayImpl(
        const __s32     _MIN
        , const __s32   _MAX
        , const __s32   _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        : MIN( _MIN )
        , DIRECTION(
            calcRangeDirection(
                _MIN
                , _MAX
            )
        )
        , DEAD_ZONE( _DEAD_ZONE )
        , HANDLER( std::move( _handler ) )
    {
    }

    template<
        typename GENERATE_DEFAULT_VALUE_T
        , typename ... ARGS_T
    >
    auto operator()(
        const GENERATE_DEFAULT_VALUE_T &    _GENERATE_DEFAULT_VALUE
        , const __s32                       _VALUE
        , ARGS_T & ...                      _args
    ) const
    {
        const auto  VALUE_FROM_MIN = ( _VALUE - this->MIN ) * this->DIRECTION;

        if( VALUE_FROM_MIN <= this->DEAD_ZONE ) {
            return _GENERATE_DEFAULT_VALUE();
        }

        return this->HANDLER(
            VALUE_FROM_MIN
            , _args ...
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEONEWAYIMPL_H
