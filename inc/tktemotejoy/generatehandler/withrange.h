#ifndef TKTEMOTEJOY_GENERATEHANDLER_WITHRANGE_H
#define TKTEMOTEJOY_GENERATEHANDLER_WITHRANGE_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <string>

template< typename T >
class GenerateHandlerWithRangeUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        const auto  KEY_MIN_ = std::string( "min" );
        const auto  KEY_MAX_ = std::string( "max" );
        const auto  KEY_DEAD_ZONE = std::string( "deadZone" );

        const auto  DEFAULT_DEAD_ZONE = Json::number_unsigned_t( 0 );

        const auto &    MIN = getJsonIntegerFromObject(
            _OBJECT
            , KEY_MIN_
        );

        const auto &    MAX = getJsonIntegerFromObject(
            _OBJECT
            , KEY_MAX_
        );

        const auto &    DEAD_ZONE = getJsonUnsignedFromObjectWithDefault(
            _OBJECT
            , DEFAULT_DEAD_ZONE
            , KEY_DEAD_ZONE
        );

        return static_cast< const T * >( this )->generateHandler(
            _OBJECT
            , MIN
            , MAX
            , DEAD_ZONE
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_WITHRANGE_H
