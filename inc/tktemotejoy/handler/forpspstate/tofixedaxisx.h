#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOFIXEDAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOFIXEDAXISX_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToFixedAxisX final : public Mapping::PressButtonHandlerForPspState
{
    const PspState::Axis    AXIS;

public:
    ToFixedAxisX(
        const __s16
    );

    void operator()(
        PspState &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOFIXEDAXISX_H
