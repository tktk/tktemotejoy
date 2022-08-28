#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct GetJsonIntegerFromObject
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonIntegerFromObject(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonIntegerFromObjectTest = GetJsonTest< GetJsonIntegerFromObject >;

    struct GetJsonIntegerFromObjectNotRequired
    {
        template< typename ... ARGS_T >
        auto operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonIntegerFromObjectNotRequired(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonIntegerFromObjectNotRequiredTest = GetJsonNotRequiredTest< GetJsonIntegerFromObjectNotRequired >;
}

TEST_F(
    GetJsonIntegerFromObjectTest
    , FromObject
)
{
    this->test(
        R"({
    "key" : 10
})"
        , "key"
        , 10
    );
}

TEST_F(
    GetJsonIntegerFromObjectTest
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
    GetJsonIntegerFromObjectTest
    , FailedNotInteger
)
{
    this->testAnyThrow(
        R"({
    "key" : "NOT INTEGER"
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値が整数ではない"
    );
}

TEST_F(
    GetJsonIntegerFromObjectNotRequiredTest
    , FromObjectNotRequired
)
{
    this->test(
        R"({
    "key" : 10
})"
        , 20
        , "key"
        , 10
    );
}

TEST_F(
    GetJsonIntegerFromObjectNotRequiredTest
    , NotExists
)
{
    this->test(
        R"({
})"
        , 20
        , "key"
        , 20
    );
}

//TODO FailedNotInteger
