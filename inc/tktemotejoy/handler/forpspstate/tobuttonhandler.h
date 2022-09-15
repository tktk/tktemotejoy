#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLER_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLER_H

#include "tktemotejoy/handler/forpspstate/withrangeoneway.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>

class ToButtonHandlerForPspStateImpl final
{
    Mapping::PressButtonHandlerForPspStateUnique    handlerUnique;

public:
    ToButtonHandlerForPspStateImpl(
        Mapping::PressButtonHandlerForPspStateUnique &&
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToButtonHandlerForPspState = WithRangeOneWayForPspState< ToButtonHandlerForPspStateImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLER_H
