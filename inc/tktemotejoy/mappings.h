#ifndef TKTEMOTEJOY_MAPPINGS_H
#define TKTEMOTEJOY_MAPPINGS_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/joystickstate.h"
#include <vector>

class Mappings final
{
public:
    using Impl = std::vector< Mapping >;

private:
    const Impl      IMPL;
    Impl::size_type mappingIndex;

public:
    Mappings(
        Impl &&
        , const Impl::size_type
    );

    void joystickStateToPspState(
        PspState &
        , const JoystickState &
    );
};

#endif  // TKTEMOTEJOY_MAPPINGS_H
