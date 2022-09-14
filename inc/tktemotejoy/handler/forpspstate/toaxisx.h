#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToAxisX_newImpl final
{
    const __s16 LIMIT;

public:
    ToAxisX_newImpl(
        const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToAxisX_new = WithRangeForPspState< ToAxisX_newImpl >;

//REMOVEME
class ToAxisXImpl final
{
    const __s16 MAX;

public:
    ToAxisXImpl(
        const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

//REMOVEME
using ToAxisX = WithDeadZoneForPspState< ToAxisXImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
