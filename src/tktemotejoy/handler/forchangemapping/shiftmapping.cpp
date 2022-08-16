#include "tktemotejoy/handler/forchangemapping/shiftmapping.h"
#include <linux/joystick.h>
#include <cstddef>

ShiftMapping::ShiftMapping(
    const std::size_t   _MAPPING_INDEX
)
    : MAPPING_INDEX( _MAPPING_INDEX )
{
}

std::size_t ShiftMapping::operator()(
    const __s16
    , std::size_t &
    , const std::size_t
) const
{
    return this->MAPPING_INDEX;
}
