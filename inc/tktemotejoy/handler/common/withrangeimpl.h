#ifndef TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEIMPL_H
#define TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEIMPL_H

#include "tktemotejoy/handler/common/calcrangedirection.h"
#include "tktemotejoy/handler/common/calcmintocenter.h"
#include <linux/input.h>
#include <utility>
#include <cmath>

template< typename HANDLER_T >
class WithRangeImpl final
{
    const __s32 MIN;
    const __s32 DIRECTION;
    const __s32 MIN_TO_CENTER;
    const __s32 DEAD_ZONE;

    const HANDLER_T HANDLER;

public:
    WithRangeImpl(
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
        , MIN_TO_CENTER(
            calcMinToCenter(
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
        const auto  MIN_TO_VALUE = ( _VALUE - this->MIN ) * this->DIRECTION;

        const auto  VALUE_FROM_CENTER = MIN_TO_VALUE - this->MIN_TO_CENTER;

        if( std::abs( VALUE_FROM_CENTER ) <= this->DEAD_ZONE ) {
            return _GENERATE_DEFAULT_VALUE();
        }

        return this->HANDLER(
            VALUE_FROM_CENTER
            , _args ...
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEIMPL_H
