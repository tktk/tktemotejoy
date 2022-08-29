#ifndef TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
#define TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <linux/joystick.h>
#include <string>

template< typename T >
class GenerateHandlerWithDeadZoneUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        const auto  KEY_DEAD_ZONE = std::string( "deadZone" );
        const auto  DEFAULT_DEAD_ZONE = __s16( 0 );

        const auto &    DEAD_ZONE = getJsonIntegerFromObjectWithDefault(
            _OBJECT
            , DEFAULT_DEAD_ZONE
            , KEY_DEAD_ZONE
        );

        return static_cast< const T * >( this )->operatorCallImpl(
            _OBJECT
            , DEAD_ZONE
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
