#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

ToAxisXImpl::ToAxisXImpl(
    const __s32     _LIMIT
    , const __s32   _ERASE_DEAD_ZONE
)
    : LIMIT( _LIMIT )
    , ERASE_DEAD_ZONE( _ERASE_DEAD_ZONE )
{
}

void ToAxisXImpl::operator()(
    const __s32     _VALUE
    , PspState &    _pspState
) const
{
    _pspState.operateAxisX(
        calcPspStateAxis(
            _VALUE
            , this->LIMIT
            , this->ERASE_DEAD_ZONE
        )
    );
}

//REMOVEME
ToAxisXImpl_old::ToAxisXImpl_old(
    const __s32 _LIMIT
)
    : LIMIT( _LIMIT )
{
}

//REMOVEME
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
