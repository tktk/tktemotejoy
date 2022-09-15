#ifndef TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEONEWAYIMPL_H
#define TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEONEWAYIMPL_H

#include <linux/input.h>
#include <utility>
#include <cmath>

template< typename HANDLER_T >
class WithRangeOneWayImpl final
{
    const __s16 MIN;
    const __s16 DIRECTION;
    const __s16 DEAD_ZONE;

    const HANDLER_T HANDLER;

    //TODO 要関数化
    static auto calcDirection(
        const __s16     _MIN
        , const __s16   _MAX
    )
    {
        return _MIN < _MAX ? 1 : -1;
    }

public:
    WithRangeOneWayImpl(
        const __s16     _MIN
        , const __s16   _MAX
        , const __s16   _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        : MIN( _MIN )
        , DIRECTION(
            WithRangeOneWayImpl::calcDirection(
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
        , const __s16                       _VALUE
        , ARGS_T & ...                      _args
    ) const
    {
        //TODO
/*
        const auto  MIN_TO_VALUE = ( _VALUE - this->MIN ) * this->DIRECTION;

        const auto  VALUE_FROM_CENTER = MIN_TO_VALUE - this->MIN_TO_CENTER;

        if( std::abs( VALUE_FROM_CENTER ) <= this->DEAD_ZONE ) {
            return _GENERATE_DEFAULT_VALUE();
        }
*/

        return this->HANDLER(
            192
            , _args ...
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_COMMON_WITHRANGEONEWAYIMPL_H
