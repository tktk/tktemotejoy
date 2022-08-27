#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <stdexcept>

namespace {
    template< typename ... PARENT_KEYS_T >
    struct TestGetJsonString
    {
        const auto & operator()(
            const Json &                _JSON
            , const std::string &
            , const PARENT_KEYS_T & ...
        ) const
        {
            return _JSON.get_ref< const Json::string_t & >();
        }
    };

    class GetJsonFromObjectTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &     _JSON_STRING
            , const std::string &   _KEY
            , const std::string &   _EXPECTED
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            const auto &    STRING = getJsonFromObject< TestGetJsonString<> >(
                OBJECT
                , _KEY
            );

            ASSERT_EQ( _EXPECTED, STRING );
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
                getJsonFromObject<
                    TestGetJsonString<
                        const std::string &
                        , const std::string &
                    >
                >(
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
    GetJsonFromObjectTest
    , Standard
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
