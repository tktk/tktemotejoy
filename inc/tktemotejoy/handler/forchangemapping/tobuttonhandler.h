#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLER_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLER_H

#include "tktemotejoy/handler/forchangemapping/withrangeoneway.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <cstddef>

class ToButtonHandlerForChangeMappingImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerUnique;

public:
    ToButtonHandlerForChangeMappingImpl(
        Mapping::PressButtonHandlerForChangeMappingUnique &&
    );

    std::size_t operator()(
        const __s32
        , std::size_t &
        , const std::size_t
    ) const;
};

using ToButtonHandlerForChangeMapping = WithRangeOneWayForChangeMapping< ToButtonHandlerForChangeMappingImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLER_H
