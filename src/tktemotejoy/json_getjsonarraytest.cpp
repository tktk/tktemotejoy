#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsontest.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct GetJsonArray
    {
        template< typename ... PARENT_KEYS_T >
        const auto & operator()(
            const Json::object_t &      _OBJECT
            , const std::string &       _KEY
            , const PARENT_KEYS_T & ... _PARENT_KEYS
        ) const
        {
            return getJsonArrayFromObject(
                _OBJECT
                , _KEY
                , _PARENT_KEYS ...
            );
        }
    };

    using GetJsonArrayTest = GetJsonTest< GetJsonArray >;
}

TEST_F(
    GetJsonArrayTest
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
    GetJsonArrayTest
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
    GetJsonArrayTest
    , FailedNotArrayFromObject
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
