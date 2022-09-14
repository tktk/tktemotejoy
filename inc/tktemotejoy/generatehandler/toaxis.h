#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H

#include "tktemotejoy/generatehandler/withrange.h"
#include "tktemotejoy/generatehandler/withdeadzone.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <linux/input.h>
#include <string>

template< typename GENERATE_TO_AXIS_UNIQUE_T >
class GenerateToAxisUnique_new : public GenerateHandlerWithRangeUnique< GenerateToAxisUnique_new< GENERATE_TO_AXIS_UNIQUE_T > >
{
public:
    auto generateHandler(
        const Json::object_t &  _OBJECT
        , const __s16           _MIN
        , const __s16           _MAX
        , const __s16           _DEAD_ZONE
    ) const
    {
/*
        const auto  KEY_MAX_ = std::string( "max" );
        const auto  DEFAULT_MAX = Json::number_integer_t( 0x7fff );

        const auto &    MAX = getJsonIntegerFromObjectWithDefault(
            _OBJECT
            , DEFAULT_MAX
            , KEY_MAX_
        );

        const auto  MAX_S16 = __s16( MAX );
*/

        return GENERATE_TO_AXIS_UNIQUE_T()(
            100
            , 200
            , 300
            , 400
        );
    }
};

//REMOVEME
template< typename GENERATE_TO_AXIS_UNIQUE_T >
class GenerateToAxisUnique : public GenerateHandlerWithDeadZoneUnique< GenerateToAxisUnique< GENERATE_TO_AXIS_UNIQUE_T > >
{
public:
    auto operatorCallImpl(
        const Json::object_t &  _OBJECT
        , const __s16           _DEAD_ZONE
    ) const
    {
        const auto  KEY_MAX_ = std::string( "max" );
        const auto  DEFAULT_MAX = Json::number_integer_t( 0x7fff );

        const auto &    MAX = getJsonIntegerFromObjectWithDefault(
            _OBJECT
            , DEFAULT_MAX
            , KEY_MAX_
        );

        const auto  MAX_S16 = __s16( MAX );

        return GENERATE_TO_AXIS_UNIQUE_T()(
            _DEAD_ZONE
            , MAX_S16
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H
