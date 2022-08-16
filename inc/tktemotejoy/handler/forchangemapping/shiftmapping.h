#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_SHIFTMAPPING_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_SHIFTMAPPING_H

#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>

class ShiftMapping final : public Mapping::HandlerForChangeMapping
{
    const std::size_t   MAPPING_INDEX;

public:
    ShiftMapping(
        const std::size_t
    );

    std::size_t operator()(
        const __s16
        , std::size_t &
        , const std::size_t
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_SHIFTMAPPING_H
