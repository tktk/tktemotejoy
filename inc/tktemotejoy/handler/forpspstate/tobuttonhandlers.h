#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H

#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>

class ToButtonHandlersForPspState_newImpl final
{
    Mapping::PressButtonHandlerForPspStateUnique    handlerMinusUnique;
    Mapping::PressButtonHandlerForPspStateUnique    handlerPlusUnique;

public:
    ToButtonHandlersForPspState_newImpl(
        Mapping::PressButtonHandlerForPspStateUnique &&
        , Mapping::PressButtonHandlerForPspStateUnique &&
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

using ToButtonHandlersForPspState_new = WithRangeForPspState< ToButtonHandlersForPspState_newImpl >;

//REMOVEME
class ToButtonHandlersForPspStateImpl final
{
    Mapping::PressButtonHandlerForPspStateUnique    handler1Unique;
    Mapping::PressButtonHandlerForPspStateUnique    handler2Unique;

public:
    ToButtonHandlersForPspStateImpl(
        Mapping::PressButtonHandlerForPspStateUnique &&
        , Mapping::PressButtonHandlerForPspStateUnique &&
    );

    void operator()(
        const __s16
        , PspState &
    ) const;
};

//REMOVEME
using ToButtonHandlersForPspState = WithDeadZoneForPspState< ToButtonHandlersForPspStateImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOBUTTONHANDLERS_H
