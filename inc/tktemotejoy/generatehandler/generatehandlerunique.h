#ifndef TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H
#define TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include <string>

template<
    typename HANDLER_UNIQUE_T
    , typename GET_TYPE_T
    , typename GENERATE_HANDLER_UNIQUE_T
    , typename ... ARGS_T
>
HANDLER_UNIQUE_T generateHandlerUnique(
    const Json::object_t &  _OBJECT
    , const ARGS_T & ...    _ARGS
)
{
    const auto  KEY_TYPE = std::string( "type" );

    const auto  TYPE_PTR = getJsonStringFromObjectNotRequired(
        _OBJECT
        , KEY_TYPE
    );
    if( TYPE_PTR == nullptr ) {
        return HANDLER_UNIQUE_T();
    }

    if( *TYPE_PTR != GET_TYPE_T()() ) {
        return HANDLER_UNIQUE_T();
    }

    return GENERATE_HANDLER_UNIQUE_T()(
        _OBJECT
        , _ARGS ...
    );
}

#endif  // TKTEMOTEJOY_GENERATEHANDLER_GENERATEHANDLERUNIQUE_H
