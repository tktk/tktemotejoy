#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

ToAxisXImpl::ToAxisXImpl(
    const __s16 _LIMIT
)
    : LIMIT( _LIMIT )
{
}

void ToAxisXImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    _pspState.operateAxisX(
        calcPspStateAxis(
            _VALUE
            , this->LIMIT
        )
    );
}
