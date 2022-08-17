#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H

#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

class ToAxisXImpl final
{
    const __s16 MAX;

public:
    ToAxisXImpl(
        const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToAxisX = WithDeadZone< ToAxisXImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
