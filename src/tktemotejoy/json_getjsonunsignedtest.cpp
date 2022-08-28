#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct GetJsonUnsigned
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json &                _JSON
            , const std::string &       _KEY
            , const PARENT_KEYS_T & ... _PARENT_KEYS
        ) const
        {
            const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

            return getJsonUnsignedFromObject(
                OBJECT
                , _KEY
                , _PARENT_KEYS ...
            );
        }
    };

    using GetJsonUnsignedTest = GetJsonTest< GetJsonUnsigned >;
}

TEST_F(
    GetJsonUnsignedTest
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
    GetJsonUnsignedTest
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
    GetJsonUnsignedTest
    , FailedNotUnsignedFromObject
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
