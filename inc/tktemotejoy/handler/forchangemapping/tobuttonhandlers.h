#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H

#include "tktemotejoy/handler/forchangemapping/withrange.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <cstddef>

class ToButtonHandlersForChangeMappingImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerMinusUnique;
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerPlusUnique;

public:
    ToButtonHandlersForChangeMappingImpl(
        Mapping::PressButtonHandlerForChangeMappingUnique &&
        , Mapping::PressButtonHandlerForChangeMappingUnique &&
    );

    std::size_t operator()(
        const __s16
        , std::size_t &
        , const std::size_t
    ) const;
};

using ToButtonHandlersForChangeMapping = WithRangeForChangeMapping< ToButtonHandlersForChangeMappingImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
