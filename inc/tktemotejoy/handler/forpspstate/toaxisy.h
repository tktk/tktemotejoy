#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

//REMOVEME
class ToAxisYImpl_old final
{
    const __s32 LIMIT;

public:
    ToAxisYImpl_old(
        const __s32
    );

    void operator()(
        const __s32
        , PspState &
    ) const;
};

//REMOVEME
using ToAxisY_old = WithRangeForPspState< ToAxisYImpl_old >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
