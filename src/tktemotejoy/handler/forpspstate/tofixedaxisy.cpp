#include "tktemotejoy/handler/forpspstate/tofixedaxisy.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/common.h"

ToFixedAxisY::ToFixedAxisY(
    const __s16 _AXIS
)
    //TODO
/*
    : AXIS( jsEventAxisToPspStateAxis( _AXIS ) )
*/
    : AXIS( 0 )
{
}

void ToFixedAxisY::operator()(
    PspState &  _pspState
) const
{
    _pspState.operateAxisY( this->AXIS );
}
