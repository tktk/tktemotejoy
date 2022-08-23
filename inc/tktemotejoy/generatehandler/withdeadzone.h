#ifndef TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
#define TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H

#include "tktemotejoy/customjson.h"

template< typename T >
class GenerateHandlerWithDeadZoneUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        //TODO
        return static_cast< const T * >( this )->operatorCallImpl(
            _OBJECT
            , 10
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
