#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/jseventaxistopspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

ToAxisY_newImpl::ToAxisY_newImpl(
    const __s16 _LIMIT
)
    : LIMIT( _LIMIT )
{
}

void ToAxisY_newImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    //TODO
/*
    _pspState.operateAxisY(
        calcPspStateAxis(
            _VALUE
            , this->LIMIT
        )
    );
*/
}

//REMOVEME
ToAxisYImpl::ToAxisYImpl(
    const __s16 _MAX
)
    : MAX( _MAX )
{
}

//REMOVEME
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
