#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H

#include "tktemotejoy/handler/forchangemapping/withrange.h"
#include "tktemotejoy/handler/forchangemapping/withdeadzone.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <cstddef>

class ToButtonHandlersForChangeMapping_newImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerMinusUnique;
    Mapping::PressButtonHandlerForChangeMappingUnique   handlerPlusUnique;

public:
    ToButtonHandlersForChangeMapping_newImpl(
        Mapping::PressButtonHandlerForChangeMappingUnique &&
        , Mapping::PressButtonHandlerForChangeMappingUnique &&
    );

    std::size_t operator()(
        const __s16
        , std::size_t &
        , const std::size_t
    ) const;
};

using ToButtonHandlersForChangeMapping_new = WithRangeForChangeMapping< ToButtonHandlersForChangeMapping_newImpl >;

//REMOVEME
class ToButtonHandlersForChangeMappingImpl final
{
    Mapping::PressButtonHandlerForChangeMappingUnique   handler1Unique;
    Mapping::PressButtonHandlerForChangeMappingUnique   handler2Unique;

public:
    ToButtonHandlersForChangeMappingImpl(
        Mapping::PressButtonHandlerForChangeMappingUnique &&
        , Mapping::PressButtonHandlerForChangeMappingUnique &&
    );

    std::size_t operator()(
        const __s16
        , std::size_t &
        , const std::size_t
    ) const;
};

//REMOVEME
using ToButtonHandlersForChangeMapping = WithDeadZoneForChangeMapping< ToButtonHandlersForChangeMappingImpl >;

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOBUTTONHANDLERS_H
