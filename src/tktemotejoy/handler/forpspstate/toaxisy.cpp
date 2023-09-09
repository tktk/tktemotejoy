#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

ToAxisYImpl::ToAxisYImpl(
    const __s32     _LIMIT
    , const __s32   _ERASE_DEAD_ZONE
)
    : LIMIT( _LIMIT )
    , ERASE_DEAD_ZONE( _ERASE_DEAD_ZONE )
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
            , this->ERASE_DEAD_ZONE
        )
    );
}

//REMOVEME
ToAxisYImpl_old::ToAxisYImpl_old(
    const __s32 _LIMIT
)
    : LIMIT( _LIMIT )
{
}

//REMOVEME
void ToAxisYImpl_old::operator()(
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
