#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H

#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

class ToAxisYImpl final
{
    const __s16 MAX;

public:
    ToAxisYImpl(
        const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToAxisY = WithDeadZone< ToAxisYImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
