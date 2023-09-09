#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToAxisXImpl final
{
    const __s32 LIMIT;
    const __s32 ERASE_DEAD_ZONE;

public:
    ToAxisXImpl(
        const __s32
        , const __s32
    );

    void operator()(
        const __s32
        , PspState &
    ) const;
};

using ToAxisX = WithRangeForPspState< ToAxisXImpl >;

//REMOVEME
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

//REMOVEME
using ToAxisX_old = WithRangeForPspState< ToAxisXImpl_old >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
