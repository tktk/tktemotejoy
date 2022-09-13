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
    const __s16 DISTANCE_CENTER;
    const __s16 DEAD_ZONE;

    const HANDLER_T HANDLER;

    auto calcDistanceFromMin(
        const __s16 _VALUE
    ) const
    {
        return std::abs( _VALUE - this->MIN );
    }

    auto calcDistanceCenter(
        const __s16 _MAX
    ) const
    {
        const auto  DISTANCE_MIN_TO_MAX = this->calcDistanceFromMin( _MAX + 1 );    // 奇数の場合に中央値を切り上げるため+1

        return DISTANCE_MIN_TO_MAX / 2;
    }

public:
    WithRangeForPspState(
        const __s16     _MIN
        , const __s16   _MAX
        , const __s16   _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        : MIN( _MIN )
        , DISTANCE_CENTER( this->calcDistanceCenter( _MAX ) )
        , DEAD_ZONE( _DEAD_ZONE )
        , HANDLER( std::move( _handler ) )
    {
    }

    void operator()(
        const __s16     _VALUE
        , PspState &    _pspState
    ) const override
    {
        const auto  DISTANCE_MIN_TO_VALUE = this->calcDistanceFromMin( _VALUE );

        const auto  VALUE_FROM_CENTER = DISTANCE_MIN_TO_VALUE - this->DISTANCE_CENTER;

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
