#include "tktemotejoy/handler/forpspstate/tofixedaxisy.h"
#include "tktemotejoy/pspstate.h"

ToFixedAxisY::ToFixedAxisY(
    const __s16 _AXIS
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
