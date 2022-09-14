#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include "tktemotejoy/handler/forpspstate/jseventaxistopspstateaxis.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

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
    _pspState.operateAxisX(
        calcPspStateAxis(
            _VALUE
            , this->LIMIT
        )
    );
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
