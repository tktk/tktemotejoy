#ifndef TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <string>

template< typename GENERATE_CHANGE_MAPPING_UNIQUE_T >
class GenerateChangeMappingUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        const auto  KEY_MAPPING = std::string( "mapping" );

        const auto &    MAPPING = getJsonUnsignedFromObject(
            _OBJECT
            , KEY_MAPPING
        );

        return GENERATE_CHANGE_MAPPING_UNIQUE_T()( MAPPING );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
