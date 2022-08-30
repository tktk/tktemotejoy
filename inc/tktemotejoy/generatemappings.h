#ifndef TKTEMOTEJOY_GENERATEMAPPINGS_H
#define TKTEMOTEJOY_GENERATEMAPPINGS_H

#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include <cstddef>

Mappings generateMappings(
    const Json &
    , const std::size_t &
    , const std::size_t &
);

//REMOVEME
Mappings generateMappings(
    const Json &
);

#endif  // TKTEMOTEJOY_GENERATEMAPPINGS_H
