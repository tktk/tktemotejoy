#ifndef TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H
#define TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H

#include "tktemotejoy/customjson.h"

template<
    typename HANDLER_UNIQUE_T
    , typename GET_TYPE_T
    , typename GENERATE_HANDLER_UNIQUE_T
>
HANDLER_UNIQUE_T generateHandlerUnique(
    const Json::object_t &  _OBJECT
)
{
    if( _OBJECT.at( "type" ).get_ref< const Json::string_t & >() != GET_TYPE_T()() ) {
        return HANDLER_UNIQUE_T();
    }

    return GENERATE_HANDLER_UNIQUE_T()( _OBJECT );
}

#endif  // TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H
