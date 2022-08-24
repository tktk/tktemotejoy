#ifndef TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
#define TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"
#include <string>
#include <cstddef>

template< typename GENERATE_CHANGE_MAPPING_UNIQUE_T >
class GenerateChangeMappingUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        const auto  KEY_MAPPING = std::string( "mapping" );

        const auto  IT = _OBJECT.find( KEY_MAPPING );
        if( IT == _OBJECT.end() ) {
            throw jsonIsNotExists( KEY_MAPPING );
        }

        const auto &    MAPPING_JSON = IT->second;
        if( MAPPING_JSON.is_number_unsigned() == false ) {
            throw jsonIsNotUnsigned( KEY_MAPPING );
        }

        const auto &    MAPPING = MAPPING_JSON.get_ref< const Json::number_integer_t & >();

        return GENERATE_CHANGE_MAPPING_UNIQUE_T()( MAPPING );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_CHANGEMAPPING_H
