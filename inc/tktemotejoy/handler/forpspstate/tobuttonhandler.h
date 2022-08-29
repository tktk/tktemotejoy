#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLER_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLER_H

#include "tktemotejoy/handler/forpspstate/withdeadzoneunsigned.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>

class ToButtonHandlerForPspStateImpl final
{
    Mapping::PressButtonHandlerForPspStateUnique    handlerUnique;

public:
    ToButtonHandlerForPspStateImpl(
        Mapping::PressButtonHandlerForPspStateUnique &&
    );

    void operator()(
        const __u16
        , PspState &
    ) const;
};

using ToButtonHandlerForPspState = WithDeadZoneUnsignedForPspState< ToButtonHandlerForPspStateImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLER_H
