#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <utility>

ToButtonHandlersForPspStateImpl::ToButtonHandlersForPspStateImpl(
    Mapping::PressButtonHandlerForPspStateUnique &&     _handlerMinusUnique
    , Mapping::PressButtonHandlerForPspStateUnique &&   _handlerPlusUnique
)
    : handlerMinusUnique( std::move( _handlerMinusUnique ) )
    , handlerPlusUnique( std::move( _handlerPlusUnique ) )
{
}

void ToButtonHandlersForPspStateImpl::operator()(
    const __s32     _VALUE
    , PspState &    _pspState
) const
{
    const auto &    HANDLER = *( _VALUE < 0 ? this->handlerMinusUnique : this->handlerPlusUnique );

    HANDLER( _pspState );
}
