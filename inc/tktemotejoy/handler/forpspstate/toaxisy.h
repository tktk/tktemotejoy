#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

//FIXME
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

//FIXME
using ToAxisY_new = WithRangeForPspState< ToAxisY_newImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISY_H
