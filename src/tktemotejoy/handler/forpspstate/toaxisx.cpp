#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/common.h"
#include <linux/joystick.h>

ToAxisXImpl::ToAxisXImpl(
    const __s16 _MAX
)
    : MAX( _MAX )
{
}

void ToAxisXImpl::operator()(
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
