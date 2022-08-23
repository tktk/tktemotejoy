#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_DUMMY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_DUMMY_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"

class DummyForPspState final : public Mapping::PressButtonHandlerForPspState
{
public:
    DummyForPspState(
    );

    void operator()(
        PspState &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_DUMMY_H
