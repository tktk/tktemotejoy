#include "tktemotejoy/handler/forchangemapping/tobuttonhandlers.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

ToButtonHandlersForChangeMappingImpl::ToButtonHandlersForChangeMappingImpl(
    Mapping::PressButtonHandlerForChangeMappingUnique &&    _handler1Unique
    , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handler2Unique
)
    : handler1Unique( std::move( _handler1Unique ) )
    , handler2Unique( std::move( _handler2Unique ) )
{
}

std::size_t ToButtonHandlersForChangeMappingImpl::operator()(
    const __s16         _VALUE
    , std::size_t &     _mappingIndex
    , const std::size_t _CURRENT_MAPPING_INDEX
) const
{
    const auto &    HANDLER = *( _VALUE < 0 ? this->handler1Unique : this->handler2Unique );

    return HANDLER(
        _mappingIndex
        , _CURRENT_MAPPING_INDEX
    );
}