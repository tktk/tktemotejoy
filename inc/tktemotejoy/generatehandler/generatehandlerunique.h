#ifndef TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H
#define TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H

#include "tktemotejoy/customjson.h"
#include <string>

template<
    typename HANDLER_UNIQUE_T
    , typename GET_TYPE_T
    , typename GENERATE_HANDLER_UNIQUE_T
>
HANDLER_UNIQUE_T generateHandlerUnique(
    const Json::object_t &  _OBJECT
)
{
    const auto  KEY_TYPE = std::string( "type" );

    const auto  IT = _OBJECT.find( KEY_TYPE );
    if( IT == _OBJECT.end() ) {
        return HANDLER_UNIQUE_T();
    }

    const auto &    TYPE = IT->second;
    if( TYPE.is_string() != true ) {
        return HANDLER_UNIQUE_T();  //TODO 例外を投げる
    } else if( TYPE.get_ref< const Json::string_t & >() != GET_TYPE_T()() ) {
        return HANDLER_UNIQUE_T();
    }

    return GENERATE_HANDLER_UNIQUE_T()( _OBJECT );
}

#endif  // TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H
