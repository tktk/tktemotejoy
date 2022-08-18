#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOCHANGEMAPPINGHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOCHANGEMAPPINGHANDLERS_H

#include "tktemotejoy/handler/forchangemapping/withdeadzone.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>

class ToChangeMappingHandlersImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handler1Unique;
    Mapping::PressButtonHandlerForChangeMappingUnique   handler2Unique;

public:
    ToChangeMappingHandlersImpl(
        Mapping::PressButtonHandlerForChangeMappingUnique &&
        , Mapping::PressButtonHandlerForChangeMappingUnique &&
    );

    std::size_t operator()(
        const __s16
        , std::size_t &
        , const std::size_t
    ) const;
};

using ToChangeMappingHandlers = WithDeadZoneForChangeMapping< ToChangeMappingHandlersImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOCHANGEMAPPINGHANDLERS_H
