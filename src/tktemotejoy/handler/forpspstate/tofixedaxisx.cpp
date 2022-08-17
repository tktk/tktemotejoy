#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/pspstate.h"

ToFixedAxisX::ToFixedAxisX(
    const __s16 _AXIS
)
    : AXIS( ( _AXIS + 0x8000 ) >> 8 )
{
}

void ToFixedAxisX::operator()(
    PspState &  _pspState
) const
{
    _pspState.operateAxisX( this->AXIS );
}
