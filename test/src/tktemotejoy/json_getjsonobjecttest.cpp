#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct GetJsonObjectFromJson
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const tktemotejoy::Json &   _JSON
            , const ARGS_T & ...        _ARGS
        ) const
        {
            return tktemotejoy::getJsonObjectFromJson(
                _JSON
                , _ARGS ...
            );
        }
    };

    using GetJsonObjectFromJsonTest = GetJsonTest< GetJsonObjectFromJson >;

    struct GetJsonObjectFromObject
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const tktemotejoy::Json &   _JSON
            , const ARGS_T & ...        _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const tktemotejoy::Json::object_t & >();

            return tktemotejoy::getJsonObjectFromObject(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonObjectFromObjectTest = GetJsonTest< GetJsonObjectFromObject >;

    struct GetJsonObjectFromObjectNotRequired
    {
        template< typename ... ARGS_T >
        auto operator()(
            const tktemotejoy::Json &   _JSON
            , const ARGS_T & ...        _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const tktemotejoy::Json::object_t & >();

            return tktemotejoy::getJsonObjectFromObjectNotRequired(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonObjectFromObjectNotRequiredTest = GetJsonNotRequiredTest< GetJsonObjectFromObjectNotRequired >;
}

TEST_F(
    GetJsonObjectFromJsonTest
    , FromJson
)
{
    this->test(
        R"({
    "key1" : "abc",
    "key2" : "def",
    "key3" : "ghi"
})"
        , ""
        , tktemotejoy::Json::object_t{
            { "key1", "abc" }
            , { "key2", "def" }
            , { "key3", "ghi" }
        }
    );
}

TEST_F(
    GetJsonObjectFromJsonTest
    , FailedNotObject
)
{
    this->testAnyThrow(
        R"("NOT OBJECT")"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値がオブジェクトではない"
    );
}

TEST_F(
    GetJsonObjectFromObjectTest
    , FromObject
)
{
    this->test(
        R"({
    "key" : {
        "key1" : "abc",
        "key2" : "def",
        "key3" : "ghi"
    }
})"
        , "key"
        , tktemotejoy::Json::object_t{
            { "key1", "abc" }
            , { "key2", "def" }
            , { "key3", "ghi" }
        }
    );
}

TEST_F(
    GetJsonObjectFromObjectTest
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
    GetJsonObjectFromObjectTest
    , FailedNotObject
)
{
    this->testAnyThrow(
        R"({
    "key" : "NOT OBJECT"
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値がオブジェクトではない"
    );
}

TEST_F(
    GetJsonObjectFromObjectNotRequiredTest
    , FromObjectNotRequired
)
{
    const auto  EXPECTED = tktemotejoy::Json::object_t{
        { "key1", "abc" }
        , { "key2", "def" }
        , { "key3", "ghi" }
    };

    this->test(
        R"({
    "key" : {
        "key1" : "abc",
        "key2" : "def",
        "key3" : "ghi"
    }
})"
        , "key"
        , &EXPECTED
    );
}

TEST_F(
    GetJsonObjectFromObjectNotRequiredTest
    , NotExists
)
{
    this->test(
        R"({
})"
        , "key"
        , static_cast< const tktemotejoy::Json::object_t * >( nullptr )
    );
}

TEST_F(
    GetJsonObjectFromObjectNotRequiredTest
    , FailedNotObject
)
{
    this->testAnyThrow(
        R"({
    "key" : "NOT OBJECT"
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値がオブジェクトではない"
    );
}
