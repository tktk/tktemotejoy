#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct TestGetJsonString
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const Json &            _JSON
            , const ARGS_T & ...
        ) const
        {
            return _JSON.get_ref< const Json::string_t & >();
        }
    };

    struct GetJsonFromObject
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonFromObject< TestGetJsonString >(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonFromObjectTest = GetJsonTest< GetJsonFromObject >;

    struct GetJsonFromObjectWithDefault
    {
        template< typename ... ARGS_T >
        const auto & operator()(
            const Json &            _JSON
            , const ARGS_T & ...    _ARGS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonFromObjectWithDefault< TestGetJsonString >(
                OBJECT
                , _ARGS ...
            );
        }
    };

    using GetJsonFromObjectWithDefaultTest = GetJsonWithDefaultTest< GetJsonFromObjectWithDefault >;
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

//TODO GetJsonFromObjectNotRequiredTest

TEST_F(
    GetJsonFromObjectWithDefaultTest
    , FromObjectWithDefault
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
    GetJsonFromObjectWithDefaultTest
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
