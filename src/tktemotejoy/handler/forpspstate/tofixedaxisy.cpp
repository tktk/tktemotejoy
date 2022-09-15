#include "tktemotejoy/handler/forpspstate/tofixedaxisy.h"
#include "tktemotejoy/pspstate.h"

ToFixedAxisY::ToFixedAxisY(
    const PspState::Axis    _AXIS
)
    : AXIS( _AXIS )
{
}

void ToFixedAxisY::operator()(
    PspState &  _pspState
) const
{
    _pspState.operateAxisY( this->AXIS );
}
