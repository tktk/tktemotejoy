#ifndef TKTEMOTEJOY_GENERATEHANDLER_WITHRANGE_H
#define TKTEMOTEJOY_GENERATEHANDLER_WITHRANGE_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <linux/input.h>
#include <string>

template< typename T >
class GenerateHandlerWithRangeUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        //TODO
        return static_cast< const T * >( this )->generateHandler(
            _OBJECT
            , 100
            , 200
            , 300
        );
/*
        const auto  KEY_DEAD_ZONE = std::string( "deadZone" );
        const auto  DEFAULT = Json::number_unsigned_t( 0 );

        const auto &    DEAD_ZONE = getJsonUnsignedFromObjectWithDefault(
            _OBJECT
            , DEFAULT
            , KEY_DEAD_ZONE
        );

        const auto  DEAD_ZONE_S16 = __s16( DEAD_ZONE );

        return static_cast< const T * >( this )->operatorCallImpl(
            _OBJECT
            , DEAD_ZONE_S16
        );
*/
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_WITHRANGE_H
