#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
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

//TODO
/*
TEST_F(
    GetJsonStringFromObjectNotRequiredTest
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

TEST_F(
    GetJsonStringFromObjectNotRequiredTest
    , FailedNotString
)
{
    this->testAnyThrow(
        R"({
    "key" : "NOT INTEGER"
})"
        , 20
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値が整数ではない"
    );
}
*/
