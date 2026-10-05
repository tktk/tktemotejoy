#ifndef TKTEMOTEJOY_MAPPINGNAMES_H
#define TKTEMOTEJOY_MAPPINGNAMES_H

#include <vector>
#include <string>

namespace tktemotejoy {
    using MappingNames = std::vector< std::string >;

    MappingNames::size_type calcMappingIndex(
        const MappingNames &
        , const MappingNames::value_type &
    );
}

#endif  // TKTEMOTEJOY_MAPPINGNAMES_H
