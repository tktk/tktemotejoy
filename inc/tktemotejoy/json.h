#ifndef TKTEMOTEJOY_JSON_H
#define TKTEMOTEJOY_JSON_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"

template<
    typename GET_JSON_T
    , typename ... PARENT_KEYS_T
>
const auto & getJsonFromObject(
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

    return GET_JSON_T()(
        JSON
        , _KEY
        , _PARENT_KEYS ...
    );
}

struct GetJsonArrayFromObject
{
    template< typename ... PARENT_KEYS_T >
    const auto & operator()(
        const Json &                _JSON
        , const std::string &       _KEY
        , const PARENT_KEYS_T & ... _PARENT_KEYS
    ) const
    {
        if( _JSON.is_array() == false ) {
            throw jsonIsNotArray(
                _PARENT_KEYS ...
                , _KEY
            );
        }

        return _JSON.get_ref< const Json::array_t & >();
    }
};

template< typename ... PARENT_KEYS_T >
const Json::array_t & getJsonArrayFromObject(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    return getJsonFromObject< GetJsonArrayFromObject >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
}

template< typename ... PARENT_KEYS_T >
const Json::object_t & getJsonObjectFromJson(
    const Json &                _JSON
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    if( _JSON.is_object() == false ) {
        throw jsonIsNotObject(
            _PARENT_KEYS ...
            , _KEY
        );
    }

    return _JSON.get_ref< const Json::object_t & >();
}

struct GetJsonObjectFromObject
{
    template< typename ... PARENT_KEYS_T >
    const auto & operator()(
        const Json &                _JSON
        , const std::string &       _KEY
        , const PARENT_KEYS_T & ... _PARENT_KEYS
    ) const
    {
        return getJsonObjectFromJson(
            _JSON
            , _KEY
            , _PARENT_KEYS ...
        );
    }
};

template< typename ... PARENT_KEYS_T >
const Json::object_t & getJsonObjectFromObject(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    return getJsonFromObject< GetJsonObjectFromObject >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
}

template< typename ... PARENT_KEYS_T >
const Json::object_t * getJsonObjectFromObjectNotRequired(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    //TODO
    const auto  IT = _OBJECT.find( _KEY );
/*
    if( IT == _OBJECT.end() ) {
        throw jsonIsNotExists(
            _PARENT_KEYS ...
            , _KEY
        );
    }
*/
    const auto &    JSON = IT->second;

    return &( JSON.get_ref< const Json::object_t & >() );
}

#endif  // TKTEMOTEJOY_JSON_H
