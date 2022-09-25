#ifndef TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H

#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/mappingnameerror.h"
#include <string>

//REMOVEME
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

template< typename GENERATE_CHANGE_MAPPING_UNIQUE_T >
class GenerateChangeMappingUnique_new
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
        , const MappingNames &  _MAPPING_NAMES
    ) const
    {
        const auto  KEY_MAPPING = std::string( "mapping" );

        const auto &    MAPPING_NAME = getJsonStringFromObject(
            _OBJECT
            , KEY_MAPPING
        );

        const auto  MAPPING_INDEX = calcMappingIndex(
            _MAPPING_NAMES
            , MAPPING_NAME
        );

        return GENERATE_CHANGE_MAPPING_UNIQUE_T()( MAPPING_INDEX );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
