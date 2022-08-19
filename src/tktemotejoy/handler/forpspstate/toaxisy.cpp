#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/jseventaxistopspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

ToAxisYImpl::ToAxisYImpl(
    const __s16 _MAX
)
    : MAX( _MAX )
{
}

void ToAxisYImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    _pspState.operateAxisY(
        jsEventAxisToPspStateAxis(
            _VALUE
            , this->MAX
        )
    );
}
