#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GetJsonArrayFromObject
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonArrayFromObject(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonArrayFromObjectTest = GetJsonTest< GetJsonArrayFromObject >;

    struct GetJsonArrayFromObjectNotRequired
    {
        template< typename ... ARGS_T >
        auto operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonArrayFromObjectNotRequired(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonArrayFromObjectNotRequiredTest = GetJsonNotRequiredTest< GetJsonArrayFromObjectNotRequired >;
}

TEST_F(
    GetJsonArrayFromObjectTest
    , FromObject
)
{
    this->test(
        R"({
    "key" : [
        "abc",
        "def",
        "ghi"
    ]
})"
        , "key"
        , Json::array_t{
            "abc"
            , "def"
            , "ghi"
        }
    );
}

TEST_F(
    GetJsonArrayFromObjectTest
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
    GetJsonArrayFromObjectTest
    , FailedNotArray
)
{
    this->testAnyThrow(
        R"({
    "key" : "NOT ARRAY"
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値が配列ではない"
    );
}

TEST_F(
    GetJsonArrayFromObjectNotRequiredTest
    , FromObjectNotRequired
)
{
    const auto  EXPECTED = Json::array_t{
        "abc"
        , "def"
        , "ghi"
    };

    this->test(
        R"({
    "key" : [
        "abc",
        "def",
        "ghi"
    ]
})"
        , "key"
        , &EXPECTED
    );
}

TEST_F(
    GetJsonArrayFromObjectNotRequiredTest
    , NotExists
)
{
    this->test(
        R"({
})"
        , "key"
        , static_cast< const Json::array_t * >( nullptr )
    );
}

TEST_F(
    GetJsonArrayFromObjectNotRequiredTest
    , FailedNotArray
)
{
    this->testAnyThrow(
        R"({
    "key" : "NOT ARRAY"
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値が配列ではない"
    );
}
