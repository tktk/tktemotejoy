#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOFIXEDAXISY_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOFIXEDAXISY_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

class ToFixedAxisY final : public Mapping::PressButtonHandlerForPspState
{
    const PspState::Axis    AXIS;

public:
    ToFixedAxisY(
        const __s16
    );

    void operator()(
        PspState &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOFIXEDAXISY_H
