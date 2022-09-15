#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToAxisYImpl final
{
    const __s32 LIMIT;

public:
    ToAxisYImpl(
        const __s32
    );

    void operator()(
        const __s32
        , PspState &
    ) const;
};

using ToAxisY = WithRangeForPspState< ToAxisYImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
