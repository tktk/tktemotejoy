#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct TestGetJsonString
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json &                _JSON
            , const std::string &
            , const PARENT_KEYS_T & ...
        ) const
        {
            return _JSON.get_ref< const Json::string_t & >();
        }
    };

    struct GetJsonFromObject
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json &                _JSON
            , const std::string &       _KEY
            , const PARENT_KEYS_T & ... _PARENT_KEYS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonFromObject< TestGetJsonString >(
                OBJECT
                , _KEY
                , _PARENT_KEYS ...
            );
        }
    };

    using GetJsonFromObjectTest = GetJsonTest< GetJsonFromObject >;

    struct GetJsonFromObjectNotRequired
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json &                _JSON
            , const std::string &       _KEY
            , const PARENT_KEYS_T & ... _PARENT_KEYS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonFromObjectNotRequired< TestGetJsonString >(
                OBJECT
                , _KEY
                , _PARENT_KEYS ...
            );
        }
    };

    using GetJsonFromObjectNotRequiredTest = GetJsonNotRequiredTest< GetJsonFromObjectNotRequired >;
}

TEST_F(
    GetJsonFromObjectTest
    , FromObject
)
{
    this->test(
        R"({
    "key" : "STRING"
})"
        , "key"
        , "STRING"
    );
}

TEST_F(
    GetJsonFromObjectTest
    , FailedNotExists
)
{
    this->testAnyThrow(
        R"({
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyが存在しない"
    );
}

TEST_F(
    GetJsonFromObjectNotRequiredTest
    , FromObjectNotRequired
)
{
    this->test(
        R"({
    "key" : "STRING"
})"
        , Json::string_t( "DEFAULT" )
        , "key"
        , Json::string_t( "STRING" )
    );
}

TEST_F(
    GetJsonFromObjectNotRequiredTest
    , NotExists
)
{
    this->test(
        R"({
})"
        , Json::string_t( "DEFAULT" )
        , "key"
        , Json::string_t( "DEFAULT" )
    );
}
