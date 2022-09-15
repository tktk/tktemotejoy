#ifndef TKTEMOTEJOY_MAPPINGS_H
#define TKTEMOTEJOY_MAPPINGS_H

#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/evdevstate.h"
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

    void evdevStateToPspState(
        PspState &
        , const EvdevState &
    );
};

#endif  // TKTEMOTEJOY_MAPPINGS_H
