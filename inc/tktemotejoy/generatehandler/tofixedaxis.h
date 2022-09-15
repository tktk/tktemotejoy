#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXIS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXIS_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <string>

template< typename GENERATE_TO_FIXED_AXIS_UNIQUE_T >
class GenerateToFixedAxisUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        const auto  KEY_VALUE = std::string( "value" );

        const auto &    VALUE = getJsonUnsignedFromObject(
            _OBJECT
            , KEY_VALUE
        );

        return GENERATE_TO_FIXED_AXIS_UNIQUE_T()( VALUE );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXIS_H
