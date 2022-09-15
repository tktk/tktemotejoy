#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
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
    _pspState.operateAxisY(
        calcPspStateAxis(
            _VALUE
            , this->LIMIT
        )
    );
}
