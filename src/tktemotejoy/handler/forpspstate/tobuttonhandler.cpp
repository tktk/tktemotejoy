#include "tktemotejoy/handler/forpspstate/tobuttonhandler.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <utility>

ToButtonHandlerForPspStateImpl::ToButtonHandlerForPspStateImpl(
    Mapping::PressButtonHandlerForPspStateUnique && _handlerUnique
)
    : handlerUnique( std::move( _handlerUnique ) )
{
}

void ToButtonHandlerForPspStateImpl::operator()(
    const __s32
    , PspState &    _pspState
) const
{
    ( *( this->handlerUnique ) )( _pspState );
}
