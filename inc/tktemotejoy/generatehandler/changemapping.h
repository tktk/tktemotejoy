#ifndef TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H

#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/mappingnameerror.h"
#include <string>
#include <algorithm>
#include <iterator>

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

        //TODO 要関数化
        const auto  MAPPING_NAMES_BEGIN = _MAPPING_NAMES.begin();
        const auto  MAPPING_NAMES_END = _MAPPING_NAMES.end();
        const auto  IT = std::lower_bound(
            MAPPING_NAMES_BEGIN
            , MAPPING_NAMES_END
            , MAPPING_NAME
        );
        if( IT == MAPPING_NAMES_END ) {
            throw mappingNameIsNotExists( MAPPING_NAME );
        }

        const auto  MAPPING_INDEX = std::distance(
            MAPPING_NAMES_BEGIN
            , IT
        );

        return GENERATE_CHANGE_MAPPING_UNIQUE_T()( MAPPING_INDEX );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
