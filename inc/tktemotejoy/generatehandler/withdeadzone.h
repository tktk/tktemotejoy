#ifndef TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
#define TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"
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

        __s16   deadZone;

        const auto  IT = _OBJECT.find( KEY_DEAD_ZONE );
        if( IT == _OBJECT.end() ) {
            deadZone = 0;
        } else {
            const auto &    DEAD_ZONE_JSON = IT->second;
            if( DEAD_ZONE_JSON.is_number_integer() == false ) {
                throw jsonIsNotInteger( KEY_DEAD_ZONE );
            }

            const auto &    DEAD_ZONE = DEAD_ZONE_JSON.get_ref< const Json::number_integer_t & >();

            deadZone = DEAD_ZONE;
        }

        return static_cast< const T * >( this )->operatorCallImpl(
            _OBJECT
            , deadZone
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
