#include "tktemotejoy/handler/forpspstate/dummy.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace tktemotejoy {
    DummyPressButtonHandlerForPspState::DummyPressButtonHandlerForPspState(
    )
    {
    }

    void DummyPressButtonHandlerForPspState::operator()(
        PspState &
    ) const
    {
    }

    DummyOperateAxisHandlerForPspState::DummyOperateAxisHandlerForPspState(
    )
    {
    }

    void DummyOperateAxisHandlerForPspState::operator()(
        const __s32
        , PspState &
    ) const
    {
    }
}
