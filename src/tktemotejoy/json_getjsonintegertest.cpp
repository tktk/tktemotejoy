#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct GetJsonInteger
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json &                _JSON
            , const std::string &       _KEY
            , const PARENT_KEYS_T & ... _PARENT_KEYS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonIntegerFromObject(
                OBJECT
                , _KEY
                , _PARENT_KEYS ...
            );
        }
    };

    using GetJsonIntegerTest = GetJsonTest< GetJsonInteger >;
}

TEST_F(
    GetJsonIntegerTest
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
    GetJsonIntegerTest
    , FailedNotExistsFromObject
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
    GetJsonIntegerTest
    , FailedNotIntegerFromObject
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
