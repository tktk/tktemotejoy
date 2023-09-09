#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToAxisXImpl final
{
    const __s32 LIMIT;

public:
    ToAxisXImpl(
        const __s32
    );

    void operator()(
        const __s32
        , PspState &
    ) const;
};

using ToAxisX_old = WithRangeForPspState< ToAxisXImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
