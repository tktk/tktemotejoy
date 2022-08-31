#include "tktemotejoy/handler/forchangemapping/tobuttonhandler.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

ToButtonHandlerForChangeMappingImpl::ToButtonHandlerForChangeMappingImpl(
    Mapping::PressButtonHandlerForChangeMappingUnique &&    _handlerUnique
)
    : handlerUnique( std::move( _handlerUnique ) )
{
}

std::size_t ToButtonHandlerForChangeMappingImpl::operator()(
    const __s16
    , std::size_t &     _mappingIndex
    , const std::size_t _CURRENT_MAPPING_INDEX
) const
{
    return ( *( this->handlerUnique ) )(
        _mappingIndex
        , _CURRENT_MAPPING_INDEX
    );
}
