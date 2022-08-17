#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <utility>

ToButtonHandlersImpl::ToButtonHandlersImpl(
    Mapping::PressButtonHandlerForPspStateUnique &&     _handler1Unique
    , Mapping::PressButtonHandlerForPspStateUnique &&   _handler2Unique
)
    : handler1Unique( std::move( _handler1Unique ) )
    , handler2Unique( std::move( _handler2Unique ) )
{
}

void ToButtonHandlersImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    ( *( this->handler1Unique ) )( _pspState );
}
