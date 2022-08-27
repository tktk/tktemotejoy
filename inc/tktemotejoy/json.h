#ifndef TKTEMOTEJOY_JSON_H
#define TKTEMOTEJOY_JSON_H

#include "tktemotejoy/customjson.h"

template< typename ... PARENT_KEYS_T >
const Json::array_t & getJsonArray(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    //TODO
    const auto  IT = _OBJECT.find( _KEY );
/*
    if( IT == _JSON_OBJECT.end() ) {
        throw jsonIsNotExists( ROOT_KEY_MAPPINGS );
    }
*/
    const auto &    JSON = IT->second;

    //TODO
/*
    if( JSON.is_array() == false ) {
        throw jsonIsNotArray( ROOT_KEY_MAPPINGS );
    }
*/
    return JSON.get_ref< const Json::array_t & >();
}

#endif  // TKTEMOTEJOY_JSON_H
