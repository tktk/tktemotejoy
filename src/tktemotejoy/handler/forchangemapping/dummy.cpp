#include "tktemotejoy/handler/forchangemapping/dummy.h"
#include <cstddef>

DummyForChangeMapping::DummyForChangeMapping(
)
{
}

std::size_t DummyForChangeMapping::operator()(
    std::size_t &   _mappingIndex
) const
{
    //TODO
    return 0;
}
