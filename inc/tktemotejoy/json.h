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
    return *static_cast< const Json::array_t * >( nullptr );
}

#endif  // TKTEMOTEJOY_JSON_H
