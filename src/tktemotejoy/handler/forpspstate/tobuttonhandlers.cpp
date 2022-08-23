#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <utility>

ToButtonHandlersForPspStateImpl::ToButtonHandlersForPspStateImpl(
    Mapping::PressButtonHandlerForPspStateUnique &&     _handler1Unique
    , Mapping::PressButtonHandlerForPspStateUnique &&   _handler2Unique
)
    : handler1Unique( std::move( _handler1Unique ) )
    , handler2Unique( std::move( _handler2Unique ) )
{
}

void ToButtonHandlersForPspStateImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    const auto &    HANDLER = *( _VALUE < 0 ? this->handler1Unique : this->handler2Unique );

    HANDLER( _pspState );
}
