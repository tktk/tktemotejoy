#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <vector>
#include <stdexcept>

namespace {
    class GetJsonObjectTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &                                 _JSON_STRING
            , const std::map< std::string, Json::string_t > &   _EXPECTED_OBJECT
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = getJsonObject(
                JSON
                , "key"
            );

            ASSERT_EQ( _EXPECTED_OBJECT.size(), OBJECT.size() );

            const auto  EXPECTED_OBJECT_END = _EXPECTED_OBJECT.end();
            for( const auto & ITEM : OBJECT ) {
                const auto  IT = _EXPECTED_OBJECT.find( ITEM.first );
                ASSERT_NE( EXPECTED_OBJECT_END, IT );

                const auto &    J = ITEM.second;

                ASSERT_TRUE( J.is_string() );
                EXPECT_EQ( IT->second, J.get_ref< const Json::string_t & >() );
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

            try {
                getJsonObject(
                    JSON
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
    GetJsonObjectTest
    , Standard
)
{
    this->test(
        R"({
    "key1" : "abc",
    "key2" : "def",
    "key3" : "ghi"
})"
        , {
            { "key1", "abc" }
            , { "key2", "def" }
            , { "key3", "ghi" }
        }
    );
}

TEST_F(
    GetJsonObjectTest
    , FailedNotObject
)
{
    this->testAnyThrow(
        R"("NOT OBJECT")"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値がオブジェクトではない"
    );
}
