#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H

#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>

class ToButtonHandlersImpl final
{
    Mapping::PressButtonHandlerForPspStateUnique    handler1Unique;
    Mapping::PressButtonHandlerForPspStateUnique    handler2Unique;

public:
    ToButtonHandlersImpl(
        Mapping::PressButtonHandlerForPspStateUnique &&
        , Mapping::PressButtonHandlerForPspStateUnique &&
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToButtonHandlers = WithDeadZoneForPspState< ToButtonHandlersImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H
