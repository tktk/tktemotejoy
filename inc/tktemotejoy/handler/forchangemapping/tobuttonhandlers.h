#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H

#include "tktemotejoy/handler/forchangemapping/withdeadzone.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>

class ToButtonHandlersForChangeMappingImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handler1Unique;
    Mapping::PressButtonHandlerForChangeMappingUnique   handler2Unique;

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

using ToButtonHandlersForChangeMapping = WithDeadZoneForChangeMapping< ToButtonHandlersForChangeMappingImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
