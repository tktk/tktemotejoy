#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/common.h"

ToFixedAxisX::ToFixedAxisX(
    const __s16 _AXIS
)
    : AXIS( jsEventAxisToPspStateAxis( _AXIS ) )
{
}

void ToFixedAxisX::operator()(
    PspState &  _pspState
) const
{
    _pspState.operateAxisX( this->AXIS );
}
