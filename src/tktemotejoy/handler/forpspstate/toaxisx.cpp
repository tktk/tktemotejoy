#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/handler/forpspstate/jseventaxistopspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>
#include <iostream>

ToAxisX_newImpl::ToAxisX_newImpl(
    const __s16 _LIMIT
)
    : LIMIT( _LIMIT )
{
}

void ToAxisX_newImpl::operator()(
    const __s16     _VALUE
    , PspState &    _pspState
) const
{
    //TODO 要関数化
    _pspState.operateAxisX( 0x80 + ( _VALUE * 0x80 / this->LIMIT ) );
}

//REMOVEME
ToAxisXImpl::ToAxisXImpl(
    const __s16 _MAX
)
    : MAX( _MAX )
{
}

//REMOVEME
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
