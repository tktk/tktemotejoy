#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H

#include "tktemotejoy/generatehandler/withrange.h"
#include "tktemotejoy/handler/common/calcmintocenter.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <linux/input.h>
#include <string>
#include <cmath>

//REMOVEME
template< typename GENERATE_TO_AXIS_UNIQUE_T >
class GenerateToAxisUnique_old : public GenerateHandlerWithRangeUnique< GenerateToAxisUnique_old< GENERATE_TO_AXIS_UNIQUE_T > >
{
public:
    auto generateHandler(
        const Json::object_t &  _OBJECT
        , const __s32           _MIN
        , const __s32           _MAX
        , const __s32           _DEAD_ZONE
    ) const
    {
        const auto  KEY_LIMIT = std::string( "limit" );

        const auto  DEFAULT_LIMIT = Json::number_unsigned_t(
            calcMinToCenter(
                _MIN
                , _MAX
            )
        );

        const auto &    LIMIT = getJsonUnsignedFromObjectWithDefault(
            _OBJECT
            , DEFAULT_LIMIT
            , KEY_LIMIT
        );

        return GENERATE_TO_AXIS_UNIQUE_T()(
            _MIN
            , _MAX
            , _DEAD_ZONE
            , LIMIT
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOAXIS_H
