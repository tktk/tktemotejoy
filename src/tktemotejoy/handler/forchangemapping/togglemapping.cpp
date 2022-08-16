#include "tktemotejoy/handler/forchangemapping/togglemapping.h"
#include <linux/joystick.h>
#include <cstddef>

ToggleMapping::ToggleMapping(
    const std::size_t   _MAPPING_INDEX
)
    : MAPPING_INDEX( _MAPPING_INDEX )
{
}

std::size_t ToggleMapping::operator()(
    const __s16
    , std::size_t & _mappingIndex
) const
{
    //TODO
    _mappingIndex = 5;
    return 0;
}
