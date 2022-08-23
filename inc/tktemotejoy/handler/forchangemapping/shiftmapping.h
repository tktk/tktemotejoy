#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_SHIFTMAPPING_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_SHIFTMAPPING_H

#include "tktemotejoy/mapping.h"
#include <cstddef>

class ShiftMapping final : public Mapping::PressButtonHandlerForChangeMapping
{
    const std::size_t   MAPPING_INDEX;

public:
    ShiftMapping(
        const std::size_t
    );

    std::size_t operator()(
        std::size_t &
        , const std::size_t
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_SHIFTMAPPING_H
