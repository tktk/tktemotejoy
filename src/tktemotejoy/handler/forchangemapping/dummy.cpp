#include "tktemotejoy/handler/forchangemapping/dummy.h"
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
