#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <map>
#include <stdexcept>

namespace {
    struct GetJsonObjectFromJson
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

    using GetJsonObjectFromJsonTest = GetJsonTest< GetJsonObjectFromJson >;

    struct GetJsonObjectFromObject
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json &                _JSON
            , const std::string &       _KEY
            , const PARENT_KEYS_T & ... _PARENT_KEYS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonObjectFromObject(
                OBJECT
                , _KEY
                , _PARENT_KEYS ...
            );
        }
    };

    using GetJsonObjectFromObjectTest = GetJsonTest< GetJsonObjectFromObject >;

    struct GetJsonObjectFromObjectNotRequired
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json &                _JSON
            , const std::string &       _KEY
            , const PARENT_KEYS_T & ... _PARENT_KEYS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return *getJsonObjectFromObjectNotRequired(
                OBJECT
                , _KEY
                , _PARENT_KEYS ...
            );
        }
    };

    using GetJsonObjectFromObjectNotRequiredTest = GetJsonTest< GetJsonObjectFromObjectNotRequired >;
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
        , Json::object_t{
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
        , Json::object_t{
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
    this->test(
        R"({
    "key" : {
        "key1" : "abc",
        "key2" : "def",
        "key3" : "ghi"
    }
})"
        , "key"
        , Json::object_t{
            { "key1", "abc" }
            , { "key2", "def" }
            , { "key3", "ghi" }
        }
    );
}

TEST_F(
    GetJsonObjectFromObjectNotRequiredTest
    , NotExists
)
{
    this->testNull(
        R"({
})"
        , "key"
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
