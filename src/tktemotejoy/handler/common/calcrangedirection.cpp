#include "tktemotejoy/handler/common/calcrangedirection.h"
#include <linux/input.h>

__s32 calcRangeDirection(
    const __s32     _MIN
    , const __s32   _MAX
)
{
    return _MIN <= _MAX ? 1 : -1;
}
