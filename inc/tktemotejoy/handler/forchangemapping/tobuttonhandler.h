#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLER_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLER_H

#include "tktemotejoy/handler/forchangemapping/withdeadzoneoneway.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>

class ToButtonHandlerForChangeMappingImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerUnique;

public:
    ToButtonHandlerForChangeMappingImpl(
        Mapping::PressButtonHandlerForChangeMappingUnique &&
    );

    std::size_t operator()(
        const __u16
        , std::size_t &
        , const std::size_t
    ) const;
};

using ToButtonHandlerForChangeMapping = WithDeadZoneOneWayForChangeMapping< ToButtonHandlerForChangeMappingImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLER_H
