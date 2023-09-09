#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToAxisXImpl_old final
{
    const __s32 LIMIT;

public:
    ToAxisXImpl_old(
        const __s32
    );

    void operator()(
        const __s32
        , PspState &
    ) const;
};

using ToAxisX_old = WithRangeForPspState< ToAxisXImpl_old >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
