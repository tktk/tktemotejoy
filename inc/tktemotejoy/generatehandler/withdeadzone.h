#ifndef TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
#define TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H

#include "tktemotejoy/customjson.h"
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
            const auto &    DEAD_ZONE = IT->second.get_ref< const Json::number_integer_t & >();

            deadZone = DEAD_ZONE;
        }

        return static_cast< const T * >( this )->operatorCallImpl(
            _OBJECT
            , deadZone
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_WITHDEADZONE_H
