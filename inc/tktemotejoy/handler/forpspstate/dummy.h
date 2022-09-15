#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_DUMMY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_DUMMY_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class DummyPressButtonHandlerForPspState final : public Mapping::PressButtonHandlerForPspState
{
public:
    DummyPressButtonHandlerForPspState(
    );

    void operator()(
        PspState &
    ) const override;
};

class DummyOperateAxisHandlerForPspState final : public Mapping::OperateAxisHandlerForPspState
{
public:
    DummyOperateAxisHandlerForPspState(
    );

    void operator()(
        const __s16
        , PspState &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_DUMMY_H
