#include "tktemotejoy/handler/common/calcmintocenter.h"
#include <linux/input.h>
#include <cmath>

__s32 calcMinToCenter(
    const __s32     _MIN
    , const __s32   _MAX
)
{
    return ( std::abs( _MAX - _MIN ) + 1 ) / 2;
}
