#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

class ToAxisY_newImpl final
{
    const __s16 LIMIT;

public:
    ToAxisY_newImpl(
        const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToAxisY_new = WithRangeForPspState< ToAxisY_newImpl >;

//REMOVEME
class ToAxisYImpl final
{
    const __s16 MAX;

public:
    ToAxisYImpl(
        const __s16
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

//REMOVEME
using ToAxisY = WithDeadZoneForPspState< ToAxisYImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
