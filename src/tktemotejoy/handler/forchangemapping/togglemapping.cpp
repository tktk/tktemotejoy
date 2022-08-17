#include "tktemotejoy/handler/forchangemapping/togglemapping.h"
#include <cstddef>

ToggleMapping::ToggleMapping(
    const std::size_t   _MAPPING_INDEX
)
    : MAPPING_INDEX( _MAPPING_INDEX )
{
}

std::size_t ToggleMapping::operator()(
    std::size_t &   _mappingIndex
) const
{
    _mappingIndex = this->MAPPING_INDEX;

    return _mappingIndex;
}
