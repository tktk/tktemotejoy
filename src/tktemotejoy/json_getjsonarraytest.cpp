#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <vector>
#include <stdexcept>

namespace {
    class GetJsonArrayTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &                     _JSON_STRING
            , const std::string &                   _KEY
            , const std::vector< Json::string_t > & _EXPECTED_ARRAY
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            const auto &    ARRAY = getJsonArrayFromObject(
                OBJECT
                , _KEY
            );

            ASSERT_EQ( _EXPECTED_ARRAY, ARRAY );
        }

        void testAnyThrow(
            const std::string &     _JSON_STRING
            , const std::string &   _KEY
            , const std::string &   _PARENT_KEY1
            , const std::string &   _PARENT_KEY2
            , const std::string &   _EXPECTED_WHAT
        )
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            try {
                getJsonArrayFromObject(
                    OBJECT
                    , _KEY
                    , _PARENT_KEY1
                    , _PARENT_KEY2
                );

                ASSERT_FALSE( true );   // ここに到達してはいけない
            } catch( const std::runtime_error & _EX ) {
                EXPECT_STREQ( _EXPECTED_WHAT.c_str(), _EX.what() );
            }
        }
    };
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
        , {
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
