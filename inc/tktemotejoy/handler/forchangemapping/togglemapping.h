#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOGGLEMAPPING_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOGGLEMAPPING_H

#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>

class ToggleMapping final : public Mapping::HandlerForChangeMapping
{
    const std::size_t   MAPPING_INDEX;

public:
    ToggleMapping(
        const std::size_t
    );

    std::size_t operator()(
        const __s16
        , std::size_t &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOGGLEMAPPING_H
