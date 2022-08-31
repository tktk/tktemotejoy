#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHDEADZONEONEWAY_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHDEADZONEONEWAY_H

#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

template< typename HANDLER_T >
class WithDeadZoneOneWayForChangeMapping final : public Mapping::OperateAxisHandlerForChangeMapping
{
    const __s16 DEAD_ZONE;

    const HANDLER_T HANDLER;

public:
    WithDeadZoneOneWayForChangeMapping(
        const __s16     _DEAD_ZONE
        , HANDLER_T &&  _handler
    )
        : DEAD_ZONE( _DEAD_ZONE )
        , HANDLER( std::move( _handler ) )
    {
    }

    std::size_t operator()(
        const __s16         _VALUE
        , std::size_t &     _mappingIndex
        , const std::size_t _CURRENT_MAPPING_INDEX
    ) const override
    {
        if( _VALUE <= this->DEAD_ZONE ) {
            return _CURRENT_MAPPING_INDEX;
        }

        return this->HANDLER(
            _VALUE
            , _mappingIndex
            , _CURRENT_MAPPING_INDEX
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHDEADZONEONEWAY_H