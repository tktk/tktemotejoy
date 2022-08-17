#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/common.h"
#include <linux/joystick.h>

ToAxisX::ToAxisX(
    const __s16     _DEAD_ZONE
    , const __s16   _MAX
)
    : DEAD_ZONE( _DEAD_ZONE )
    , MAX( _MAX )
{
}

void ToAxisX::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    _pspState.operateAxisX(
        jsEventAxisToPspStateAxis(
            _VALUE
            , this->MAX
        )
    );
}
