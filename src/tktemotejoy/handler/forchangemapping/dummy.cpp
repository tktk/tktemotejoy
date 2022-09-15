#include "tktemotejoy/handler/forchangemapping/dummy.h"
#include <linux/input.h>
#include <cstddef>

DummyPressButtonHandlerForChangeMapping::DummyPressButtonHandlerForChangeMapping(
)
{
}

std::size_t DummyPressButtonHandlerForChangeMapping::operator()(
    std::size_t &
    , const std::size_t _CURRENT_MAPPING_INDEX
) const
{
    return _CURRENT_MAPPING_INDEX;
}

DummyOperateAxisHandlerForChangeMapping::DummyOperateAxisHandlerForChangeMapping(
)
{
}

std::size_t DummyOperateAxisHandlerForChangeMapping::operator()(
    const __s32
    , std::size_t &
    , const std::size_t _CURRENT_MAPPING_INDEX
) const
{
    return _CURRENT_MAPPING_INDEX;
}
