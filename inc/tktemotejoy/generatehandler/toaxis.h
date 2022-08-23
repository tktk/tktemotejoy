#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H

#include "tktemotejoy/generatehandler/withdeadzone.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>

template< typename GENERATE_TO_AXIS_T >
class GenerateToAxisUnique : public GenerateHandlerWithDeadZoneUnique< GenerateToAxisUnique< GENERATE_TO_AXIS_T > >
{
public:
    auto operatorCallImpl(
        const Json::object_t &  _OBJECT
        , const __s16           _DEAD_ZONE
    ) const
    {
        //TODO
        return GENERATE_TO_AXIS_T()(
            _DEAD_ZONE
            , 0
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H
