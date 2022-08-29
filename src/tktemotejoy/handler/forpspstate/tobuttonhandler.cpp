#include "tktemotejoy/handler/forpspstate/tobuttonhandler.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <utility>

ToButtonHandlerForPspStateImpl::ToButtonHandlerForPspStateImpl(
    Mapping::PressButtonHandlerForPspStateUnique && _handlerUnique
)
    : handlerUnique( std::move( _handlerUnique ) )
{
}

void ToButtonHandlerForPspStateImpl::operator()(
    const __u16     _VALUE
    , PspState &    _pspState
) const
{
    //TODO
/*
    ( *( this->handlerUnique ) )( _pspState );
*/
}
