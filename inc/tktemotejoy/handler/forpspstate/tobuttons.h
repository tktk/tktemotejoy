#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONS_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONS_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"

class ToButtons final : public Mapping::PressButtonHandlerForPspState
{
    const PspState::Buttons BUTTONS;

public:
    ToButtons(
        const PspState::Buttons
    );

    void operator()(
        PspState &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONS_H
