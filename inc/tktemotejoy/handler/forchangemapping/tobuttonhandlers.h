#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H

#include "tktemotejoy/handler/forchangemapping/withrange.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <cstddef>

//FIXME
class ToButtonHandlersForChangeMapping_newImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerMinusUnique;
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerPlusUnique;

public:
    ToButtonHandlersForChangeMapping_newImpl(
        Mapping::PressButtonHandlerForChangeMappingUnique &&
        , Mapping::PressButtonHandlerForChangeMappingUnique &&
    );

    std::size_t operator()(
        const __s16
        , std::size_t &
        , const std::size_t
    ) const;
};

//FIXME
using ToButtonHandlersForChangeMapping_new = WithRangeForChangeMapping< ToButtonHandlersForChangeMapping_newImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
