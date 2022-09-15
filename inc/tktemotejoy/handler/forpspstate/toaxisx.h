#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToAxisXImpl final
{
    const __s16 LIMIT;

public:
    ToAxisXImpl(
        const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToAxisX = WithRangeForPspState< ToAxisXImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
