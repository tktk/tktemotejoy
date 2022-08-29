#ifndef TKTEMOTEJOY_JSON_H
#define TKTEMOTEJOY_JSON_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"

template<
    typename GET_JSON_T
    , typename ... PARENT_KEYS_T
>
auto getJsonFromObjectNotRequired(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    const auto  IT = _OBJECT.find( _KEY );
    if( IT == _OBJECT.end() ) {
        return static_cast<
            decltype(
                &(
                    GET_JSON_T()(
                        IT->second
                        , _KEY
                        , _PARENT_KEYS ...
                    )
                )
            )
        >( nullptr );
    }
    const auto &    JSON = IT->second;

    return &(
        GET_JSON_T()(
            JSON
            , _KEY
            , _PARENT_KEYS ...
        )
    );
}

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
    const auto  JSON_PTR = getJsonFromObjectNotRequired< GET_JSON_T >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
    if( JSON_PTR == nullptr ) {
        throw jsonIsNotExists(
            _PARENT_KEYS ...
            , _KEY
        );
    }

    return *JSON_PTR;
}

template<
    typename GET_JSON_T
    , typename DEFAULT_T
    , typename ... PARENT_KEYS_T
>
const auto & getJsonFromObjectWithDefault(
    const Json::object_t &      _OBJECT
    , const DEFAULT_T &         _DEFAULT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    const auto  JSON_PTR = getJsonFromObjectNotRequired< GET_JSON_T >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
    if( JSON_PTR == nullptr ) {
        return _DEFAULT;
    }

    return *JSON_PTR;
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
    return getJsonFromObjectNotRequired< GetJsonObjectFromObject >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
}

struct GetJsonUnsignedFromObject
{
    template< typename ... PARENT_KEYS_T >
    const auto & operator()(
        const Json &                _JSON
        , const std::string &       _KEY
        , const PARENT_KEYS_T & ... _PARENT_KEYS
    ) const
    {
        if( _JSON.is_number_unsigned() == false ) {
            throw jsonIsNotUnsigned(
                _PARENT_KEYS ...
                , _KEY
            );
        }

        return _JSON.get_ref< const Json::number_unsigned_t & >();
    }
};

template< typename ... PARENT_KEYS_T >
const Json::number_unsigned_t & getJsonUnsignedFromObject(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    return getJsonFromObject< GetJsonUnsignedFromObject >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
}

template< typename ... PARENT_KEYS_T >
const Json::number_unsigned_t & getJsonUnsignedFromObjectWithDefault(
    const Json::object_t &              _OBJECT
    , const Json::number_unsigned_t &   _DEFAULT
    , const std::string &               _KEY
    , const PARENT_KEYS_T & ...         _PARENT_KEYS
)
{
    return getJsonFromObjectWithDefault< GetJsonUnsignedFromObject >(
        _OBJECT
        , _DEFAULT
        , _KEY
        , _PARENT_KEYS ...
    );
}

struct GetJsonIntegerFromObject
{
    template< typename ... PARENT_KEYS_T >
    const auto & operator()(
        const Json &                _JSON
        , const std::string &       _KEY
        , const PARENT_KEYS_T & ... _PARENT_KEYS
    ) const
    {
        if( _JSON.is_number_integer() == false ) {
            throw jsonIsNotInteger(
                _PARENT_KEYS ...
                , _KEY
            );
        }

        return _JSON.get_ref< const Json::number_integer_t & >();
    }
};

template< typename ... PARENT_KEYS_T >
const Json::number_integer_t & getJsonIntegerFromObject(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    return getJsonFromObject< GetJsonIntegerFromObject >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
}

template< typename ... PARENT_KEYS_T >
const Json::number_integer_t & getJsonIntegerFromObjectWithDefault(
    const Json::object_t &              _OBJECT
    , const Json::number_integer_t &    _DEFAULT
    , const std::string &               _KEY
    , const PARENT_KEYS_T & ...         _PARENT_KEYS
)
{
    return getJsonFromObjectWithDefault< GetJsonIntegerFromObject >(
        _OBJECT
        , _DEFAULT
        , _KEY
        , _PARENT_KEYS ...
    );
}

struct GetJsonStringFromObject
{
    template< typename ... PARENT_KEYS_T >
    const auto & operator()(
        const Json &                _JSON
        , const std::string &       _KEY
        , const PARENT_KEYS_T & ... _PARENT_KEYS
    ) const
    {
        if( _JSON.is_string() == false ) {
            throw jsonIsNotString(
                _PARENT_KEYS ...
                , _KEY
            );
        }

        return _JSON.get_ref< const Json::string_t & >();
    }
};

template< typename ... PARENT_KEYS_T >
const Json::string_t * getJsonStringFromObjectNotRequired(
    const Json::object_t &      _OBJECT
    , const std::string &       _KEY
    , const PARENT_KEYS_T & ... _PARENT_KEYS
)
{
    return getJsonFromObjectNotRequired< GetJsonStringFromObject >(
        _OBJECT
        , _KEY
        , _PARENT_KEYS ...
    );
}

#endif  // TKTEMOTEJOY_JSON_H
