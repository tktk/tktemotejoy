#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <utility>

ToButtonHandlersForPspState_newImpl::ToButtonHandlersForPspState_newImpl(
    Mapping::PressButtonHandlerForPspStateUnique &&     _handlerMinusUnique
    , Mapping::PressButtonHandlerForPspStateUnique &&   _handlerPlusUnique
)
{
}

void ToButtonHandlersForPspState_newImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    //TODO
/*
    const auto &    HANDLER = *( _VALUE < 0 ? this->handler1Unique : this->handler2Unique );

    HANDLER( _pspState );
*/
}

//REMOVEME
ToButtonHandlersForPspStateImpl::ToButtonHandlersForPspStateImpl(
    Mapping::PressButtonHandlerForPspStateUnique &&     _handler1Unique
    , Mapping::PressButtonHandlerForPspStateUnique &&   _handler2Unique
)
    : handler1Unique( std::move( _handler1Unique ) )
    , handler2Unique( std::move( _handler2Unique ) )
{
}

//REMOVEME
void ToButtonHandlersForPspStateImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    const auto &    HANDLER = *( _VALUE < 0 ? this->handler1Unique : this->handler2Unique );

    HANDLER( _pspState );
}
