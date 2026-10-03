#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct GetJsonStringFromObject
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonStringFromObject(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonStringFromObjectTest = GetJsonTest< GetJsonStringFromObject >;

    struct GetJsonStringFromObjectNotRequired
    {
        template< typename ... ARGS_T >
        auto operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonStringFromObjectNotRequired(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonStringFromObjectNotRequiredTest = GetJsonNotRequiredTest< GetJsonStringFromObjectNotRequired >;
}

TEST_F(
    GetJsonStringFromObjectTest
    , FromObject
)
{
    this->test(
        R"({
    "key" : "value"
})"
        , "key"
        , "value"
    );
}

TEST_F(
    GetJsonStringFromObjectTest
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
    GetJsonStringFromObjectTest
    , FailedNotString
)
{
    this->testAnyThrow(
        R"({
    "key" : 10
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値が文字列ではない"
    );
}

TEST_F(
    GetJsonStringFromObjectNotRequiredTest
    , FromObjectNotRequired
)
{
    const auto  EXPECTED = std::string( "value" );

    this->test(
        R"({
    "key" : "value"
})"
        , "key"
        , &EXPECTED
    );
}

TEST_F(
    GetJsonStringFromObjectNotRequiredTest
    , NotExists
)
{
    this->test(
        R"({
})"
        , "key"
        , static_cast< const std::string * >( nullptr )
    );
}

TEST_F(
    GetJsonStringFromObjectNotRequiredTest
    , FailedNotString
)
{
    this->testAnyThrow(
        R"({
    "key" : [ "NOT STRING" ]
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値が文字列ではない"
    );
}
