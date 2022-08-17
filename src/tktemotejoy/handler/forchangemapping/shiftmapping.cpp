#include "tktemotejoy/handler/forchangemapping/shiftmapping.h"
#include <cstddef>

ShiftMapping::ShiftMapping(
    const std::size_t   _MAPPING_INDEX
)
    : MAPPING_INDEX( _MAPPING_INDEX )
{
}

std::size_t ShiftMapping::operator()(
    std::size_t &
) const
{
    return this->MAPPING_INDEX;
}
