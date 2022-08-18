#include "tktemotejoy/handler/forchangemapping/tochangemappinghandlers.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

ToChangeMappingHandlersImpl::ToChangeMappingHandlersImpl(
    Mapping::PressButtonHandlerForChangeMappingUnique &&    _handler1Unique
    , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handler2Unique
)
    : handler1Unique( std::move( _handler1Unique ) )
    , handler2Unique( std::move( _handler2Unique ) )
{
}

std::size_t ToChangeMappingHandlersImpl::operator()(
    const __s16         _VALUE
    , std::size_t &     _mappingIndex
    , const std::size_t
) const
{
    //TODO
    return ( *( this->handler1Unique ) )( _mappingIndex );
/*
    const auto &    HANDLER = *( _VALUE < 0 ? this->handler1Unique : this->handler2Unique );

    HANDLER( _pspState );
*/
}
