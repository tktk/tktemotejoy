#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>
#include <utility>
#include <cmath>

template< typename HANDLER_T >
class WithRangeForPspState final : public Mapping::OperateAxisHandlerForPspState
{
    const __s16 MIN;
    const __s16 DIRECTION;
    const __s16 MIN_TO_CENTER;
    const __s16 DEAD_ZONE;

    const HANDLER_T HANDLER;

    static auto calcDirection(
        const __s16     _MIN
        , const __s16   _MAX
    )
    {
        return _MIN < _MAX ? 1 : -1;
    }

    static auto calcMinToCenter(
        const __s16     _MIN
        , const __s16   _MAX
        , const __s16   _DIRECTION
    )
    {
        const auto  MIN_TO_MAX = ( ( _MAX + 1 ) - _MIN ) * _DIRECTION;  // 奇数の場合に中央値を切り上げるため+1

        const auto  MIN_TO_CENTER = MIN_TO_MAX / 2;

        return MIN_TO_CENTER;
    }

public:
    WithRangeForPspState(
        const __s16     _MIN
        , const __s16   _MAX
        , const __s16   _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        : MIN( _MIN )
        , DIRECTION(
            WithRangeForPspState::calcDirection(
                _MIN
                , _MAX
            )
        )
        , MIN_TO_CENTER(
            WithRangeForPspState::calcMinToCenter(
                _MIN
                , _MAX
                , this->DIRECTION
            )
        )
        , DEAD_ZONE( _DEAD_ZONE )
        , HANDLER( std::move( _handler ) )
    {
    }

    void operator()(
        const __s16     _VALUE
        , PspState &    _pspState
    ) const override
    {
        const auto  MIN_TO_VALUE = ( _VALUE - this->MIN ) * this->DIRECTION;

        const auto  VALUE_FROM_CENTER = MIN_TO_VALUE - this->MIN_TO_CENTER;

        if( std::abs( VALUE_FROM_CENTER ) <= this->DEAD_ZONE ) {
            return;
        }

        this->HANDLER(
            VALUE_FROM_CENTER
            , _pspState
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_WITHRANGE_H
