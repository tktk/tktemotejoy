#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOAXISX_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

class ToAxisX final : public Mapping::OperateAxisHandlerForPspState
{
    const __s16 DEAD_ZONE;
    const __s16 MAX;

public:
    ToAxisX(
        const __s16
        , const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOAXISX_H
