#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHRANGE_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHRANGE_H

#include "tktemotejoy/handler/common/withrangeimpl.h"
#include "tktemotejoy/mappings.h"
#include <linux/input.h>
#include <cstddef>

template< typename HANDLER_T >
class WithRangeForChangeMapping final : public Mapping::OperateAxisHandlerForChangeMapping
{
    const WithRangeImpl< HANDLER_T >    IMPL;

public:
    WithRangeForChangeMapping(
        const __s16     _MIN
        , const __s16   _MAX
        , const __s16   _DEAD_ZONE
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

    std::size_t operator()(
        const __s16         _VALUE
        , std::size_t &     _mappingIndex
        , const std::size_t _CURRENT_MAPPING_INDEX
    ) const override
    {
        return this->IMPL(
            []{ return std::size_t( 0 ); }  //TODO
            , _VALUE
            , _mappingIndex
            , _CURRENT_MAPPING_INDEX
        );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_WITHRANGE_H
