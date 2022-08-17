#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include "tktemotejoy/pspstate.h"

ToButtons::ToButtons(
    const PspState::Buttons _BUTTONS
)
    : BUTTONS( _BUTTONS )
{
}

void ToButtons::operator()(
    PspState &  _pspState
) const
{
    //TODO
}
