#ifndef TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_DUMMY_H
#define TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_DUMMY_H

#include "tktemotejoy/mapping.h"
#include <cstddef>

class DummyPressButtonHandlerForChangeMapping final : public Mapping::PressButtonHandlerForChangeMapping
{
public:
    DummyPressButtonHandlerForChangeMapping(
    );

    std::size_t operator()(
        std::size_t &
    ) const override;
};

#endif  // TKTEMOTEJOY_HANDLER_FORCHANGEMAPPING_DUMMY_H
