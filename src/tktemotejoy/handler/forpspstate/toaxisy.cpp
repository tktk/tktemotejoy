#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

ToAxisYImpl::ToAxisYImpl(
    const __s32 _LIMIT
)
    : LIMIT( _LIMIT )
{
}

void ToAxisYImpl::operator()(
    const __s32     _VALUE
    , PspState &    _pspState
) const
{
    _pspState.operateAxisY(
        calcPspStateAxis(
            _VALUE
            , this->LIMIT
        )
    );
}
