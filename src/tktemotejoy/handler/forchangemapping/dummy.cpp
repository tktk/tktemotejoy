#include "tktemotejoy/handler/forchangemapping/dummy.h"
#include <linux/joystick.h>
#include <cstddef>

DummyPressButtonHandlerForChangeMapping::DummyPressButtonHandlerForChangeMapping(
)
{
}

std::size_t DummyPressButtonHandlerForChangeMapping::operator()(
    std::size_t &   _mappingIndex
) const
{
    return _mappingIndex;
}

DummyOperateAxisHandlerForChangeMapping::DummyOperateAxisHandlerForChangeMapping(
)
{
}

std::size_t DummyOperateAxisHandlerForChangeMapping::operator()(
    const __s16
    , std::size_t &
    , const std::size_t _CURRENT_MAPPING_INDEX
) const
{
    //TODO
    return 0;
}
