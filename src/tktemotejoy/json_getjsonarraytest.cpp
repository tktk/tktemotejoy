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

            const auto &    ARRAY = getJsonArray(
                OBJECT
                , _KEY
            );

            ASSERT_EQ( _EXPECTED_ARRAY.size(), ARRAY.size() );

            auto    i = 0;
            for( const auto & J : ARRAY ) {
                ASSERT_TRUE( J.is_string() );
                EXPECT_EQ( _EXPECTED_ARRAY.at( i ), J.get_ref< const Json::string_t & >() );

                i++;
            }
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
                getJsonArray(
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
    , Standard
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
    GetJsonArrayTest
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
