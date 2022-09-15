#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>

class ToButtonHandlersForPspStateImpl final
{
    Mapping::PressButtonHandlerForPspStateUnique    handlerMinusUnique;
    Mapping::PressButtonHandlerForPspStateUnique    handlerPlusUnique;

public:
    ToButtonHandlersForPspStateImpl(
        Mapping::PressButtonHandlerForPspStateUnique &&
        , Mapping::PressButtonHandlerForPspStateUnique &&
    );

    void operator()(
        const __s32
        , PspState &
    ) const;
};

using ToButtonHandlersForPspState = WithRangeForPspState< ToButtonHandlersForPspStateImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H
