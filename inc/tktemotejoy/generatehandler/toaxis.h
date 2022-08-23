#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H

#include "tktemotejoy/generatehandler/withdeadzone.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>

template< typename GENERATE_TO_AXIS_T >
class GenerateToAxisUnique : public GenerateHandlerWithDeadZoneUnique< GenerateToAxisUnique< GENERATE_TO_AXIS_T > >
{
public:
    auto operatorCallImpl(
        const Json::object_t &  _OBJECT
        , const __s16           _DEAD_ZONE
    ) const
    {
        const auto  KEY_MAX_ = std::string( "max" );

        __s16   max;

        const auto  IT = _OBJECT.find( KEY_MAX_ );
        const auto &    MAX_JSON = IT->second;
        const auto &    MAX = MAX_JSON.get_ref< const Json::number_integer_t & >();

        max = MAX;

        return GENERATE_TO_AXIS_T()(
            _DEAD_ZONE
            , max
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H