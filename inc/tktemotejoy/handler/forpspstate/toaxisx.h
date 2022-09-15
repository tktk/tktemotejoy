#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

//FIXME
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

//FIXME
using ToAxisX_new = WithRangeForPspState< ToAxisX_newImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISX_H
