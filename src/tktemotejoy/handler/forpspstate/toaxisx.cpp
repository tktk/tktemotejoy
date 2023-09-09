#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

ToAxisXImpl_old::ToAxisXImpl_old(
    const __s32 _LIMIT
)
    : LIMIT( _LIMIT )
{
}

void ToAxisXImpl_old::operator()(
    const __s32     _VALUE
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
