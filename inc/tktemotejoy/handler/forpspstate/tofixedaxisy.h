#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOFIXEDAXISY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOFIXEDAXISY_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"

class ToFixedAxisY final : public Mapping::PressButtonHandlerForPspState
{
    const PspState::Axis    AXIS;

public:
    ToFixedAxisY(
        const PspState::Axis
    );

    void operator()(
        PspState &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOFIXEDAXISY_H
