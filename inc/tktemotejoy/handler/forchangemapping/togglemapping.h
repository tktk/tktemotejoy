#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOGGLEMAPPING_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOGGLEMAPPING_H

#include "tktemotejoy/mapping.h"
#include <cstddef>

class ToggleMapping final : public Mapping::PressButtonHandlerForChangeMapping
{
    const std::size_t   MAPPING_INDEX;

public:
    ToggleMapping(
        const std::size_t
    );

    std::size_t operator()(
        std::size_t &
        , const std::size_t
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_TOGGLEMAPPING_H
