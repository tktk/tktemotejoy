#ifndef TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONEUNSIGNED_H
#define TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONEUNSIGNED_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <linux/joystick.h>
#include <string>

template< typename T >
class GenerateHandlerWithDeadZoneUnsignedUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        const auto  KEY_DEAD_ZONE = std::string( "deadZone" );
        const auto  DEFAULT_DEAD_ZONE = Json::number_unsigned_t( 1 );

        const auto &    DEAD_ZONE = getJsonUnsignedFromObjectWithDefault(
            _OBJECT
            , DEFAULT_DEAD_ZONE
            , KEY_DEAD_ZONE
        );

        const auto  DEAD_ZONE_U16 = __u16( DEAD_ZONE );

        return static_cast< const T * >( this )->operatorCallImpl(
            _OBJECT
            , DEAD_ZONE_U16
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONEUNSIGNED_H
