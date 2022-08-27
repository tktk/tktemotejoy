#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <stdexcept>

namespace {
    struct TestGetJsonString
    {
        template< typename ... PARENT_KEYS_T >
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
        void testFromObject(
            const std::string &     _JSON_STRING
            , const std::string &   _KEY
            , const std::string &   _EXPECTED
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            const auto &    STRING = getJsonFromObject< TestGetJsonString >(
                OBJECT
                , _KEY
            );

            ASSERT_EQ( _EXPECTED, STRING );
        }

        void testFromObjectNotRequired(
            const std::string &     _JSON_STRING
            , const std::string &   _KEY
            , const std::string &   _DEFAULT
            , const std::string &   _EXPECTED
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            const auto &    STRING = getJsonFromObjectNotRequired< TestGetJsonString >(
                OBJECT
                , _DEFAULT
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
                getJsonFromObject< TestGetJsonString >(
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
    , FromObject
)
{
    this->testFromObject(
        R"({
    "key" : "STRING"
})"
        , "key"
        , "STRING"
    );
}

TEST_F(
    GetJsonFromObjectTest
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
    GetJsonFromObjectTest
    , FromObjectNotRequired
)
{
    this->testFromObjectNotRequired(
        R"({
    "key" : "STRING"
})"
        , "key"
        , "DEFAULT"
        , "STRING"
    );
}

//TODO NotExistsFromObjectNotRequired
