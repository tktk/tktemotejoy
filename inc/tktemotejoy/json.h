#ifndef TKTEMOTEJOY_JSON_H
#define TKTEMOTEJOY_JSON_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"

template< typename ... PARENT_KEYS_T >
const Json::array_t & getJsonArray(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    const auto  IT = _OBJECT.find( _KEY );
    if( IT == _OBJECT.end() ) {
        throw jsonIsNotExists(
            _PARENT_KEYS ...
            , _KEY
        );
    }
    const auto &    JSON = IT->second;

    if( JSON.is_array() == false ) {
        throw jsonIsNotArray(
            _PARENT_KEYS ...
            , _KEY
        );
    }

    return JSON.get_ref< const Json::array_t & >();
}

template< typename ... KEYS_T >
const Json::object_t & getJsonObject(
    const Json &            _JSON
    , const KEYS_T & ...    _KEYS
)
{
    //TODO
    return *static_cast< const Json::object_t * >( nullptr );
}

#endif  // TKTEMOTEJOY_JSON_H
