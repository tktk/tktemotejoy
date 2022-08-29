#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct GetJsonUnsignedFromObject
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonUnsignedFromObject(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonUnsignedFromObjectTest = GetJsonTest< GetJsonUnsignedFromObject >;

    struct GetJsonUnsignedFromObjectWithDefault
    {
        template< typename ... ARGS_T >
        auto operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonUnsignedFromObjectWithDefault(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonUnsignedFromObjectWithDefaultTest = GetJsonWithDefaultTest< GetJsonUnsignedFromObjectWithDefault >;
}

TEST_F(
    GetJsonUnsignedFromObjectTest
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
    GetJsonUnsignedFromObjectTest
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
    GetJsonUnsignedFromObjectTest
    , FailedNotUnsigned
)
{
    this->testAnyThrow(
        R"({
    "key" : "NOT UNSIGNED"
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値が符号なし整数ではない"
    );
}

TEST_F(
    GetJsonUnsignedFromObjectWithDefaultTest
    , FromObject
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

//TODO NotExists
//TODO FailedNotUnsigned
