#include "tktemotejoy/test.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <map>
#include <stdexcept>

namespace {
    class GetJsonObjectTest : public ::testing::Test
    {
        struct GetJsonObjectFromJson
        {
            template< typename ... PARENT_KEYS_T >
            const auto & operator()(
                const Json &                _JSON
                , const std::string &       _KEY
                , const PARENT_KEYS_T & ... _PARENT_KEYS
            ) const
            {
                return getJsonObjectFromJson(
                    _JSON
                    , _KEY
                    , _PARENT_KEYS ...
                );
            }
        };

        struct GetJsonObjectFromObject
        {
            template< typename ... PARENT_KEYS_T >
            const auto & operator()(
                const Json &                _JSON
                , const std::string &       _KEY
                , const PARENT_KEYS_T & ... _PARENT_KEYS
            ) const
            {
                const auto &    OBJECT = _JSON.get_ref< const Json::object_t & >();

                return getJsonObjectFromObject(
                    OBJECT
                    , _KEY
                    , _PARENT_KEYS ...
                );
            }
        };

        template< typename GET_JSON_OBJECT_T >
        void test(
            const std::string &                                 _JSON_STRING
            , const std::string &                               _KEY
            , const std::map< std::string, Json::string_t > &   _EXPECTED_OBJECT
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = GET_JSON_OBJECT_T()(
                JSON
                , _KEY
            );

            ASSERT_EQ( _EXPECTED_OBJECT.size(), OBJECT.size() );

            const auto  EXPECTED_OBJECT_END = _EXPECTED_OBJECT.end();
            for( const auto & ITEM : OBJECT ) {
                const auto  IT = _EXPECTED_OBJECT.find( ITEM.first );
                ASSERT_NE( EXPECTED_OBJECT_END, IT );

                const auto &    J = static_cast< const Json & >( ITEM.second ); // キャストを消すとコンパイルエラー

                ASSERT_TRUE( J.is_string() );
                EXPECT_EQ( IT->second, J.get_ref< const Json::string_t & >() );
            }
        }

        template< typename GET_JSON_OBJECT_T >
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
                GET_JSON_OBJECT_T()(
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

    public:
        void test(
            const std::string &                                 _JSON_STRING
            , const std::map< std::string, Json::string_t > &   _EXPECTED_OBJECT
        ) const
        {
            this->test< GetJsonObjectFromJson >(
                _JSON_STRING
                , "key"
                , _EXPECTED_OBJECT
            );
        }

        void test(
            const std::string &                                 _JSON_STRING
            , const std::string &                               _KEY
            , const std::map< std::string, Json::string_t > &   _EXPECTED_OBJECT
        ) const
        {
            this->test< GetJsonObjectFromObject >(
                _JSON_STRING
                , _KEY
                , _EXPECTED_OBJECT
            );
        }

        void testAnyThrowFromJson(
            const std::string &     _JSON_STRING
            , const std::string &   _KEY
            , const std::string &   _PARENT_KEY1
            , const std::string &   _PARENT_KEY2
            , const std::string &   _EXPECTED_WHAT
        )
        {
            this->testAnyThrow< GetJsonObjectFromJson >(
                _JSON_STRING
                , _KEY
                , _PARENT_KEY1
                , _PARENT_KEY2
                , _EXPECTED_WHAT
            );
        }

        void testAnyThrowFromObject(
            const std::string &     _JSON_STRING
            , const std::string &   _KEY
            , const std::string &   _PARENT_KEY1
            , const std::string &   _PARENT_KEY2
            , const std::string &   _EXPECTED_WHAT
        )
        {
            this->testAnyThrow< GetJsonObjectFromObject >(
                _JSON_STRING
                , _KEY
                , _PARENT_KEY1
                , _PARENT_KEY2
                , _EXPECTED_WHAT
            );
        }
    };
}

TEST_F(
    GetJsonObjectTest
    , FromJson
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
    , FailedNotObjectFromJson
)
{
    this->testAnyThrowFromJson(
        R"("NOT OBJECT")"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値がオブジェクトではない"
    );
}

TEST_F(
    GetJsonObjectTest
    , FromObject
)
{
    this->test(
        R"({
    "key" : {
        "key1" : "abc",
        "key2" : "def",
        "key3" : "ghi"
    }
})"
        , "key"
        , {
            { "key1", "abc" }
            , { "key2", "def" }
            , { "key3", "ghi" }
        }
    );
}

TEST_F(
    GetJsonObjectTest
    , FailedNotExistsFromObject
)
{
    this->testAnyThrowFromObject(
        R"({
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyが存在しない"
    );
}

TEST_F(
    GetJsonObjectTest
    , FailedNotObjectFromObject
)
{
    this->testAnyThrowFromObject(
        R"({
    "key" : "NOT OBJECT"
})"
        , "key"
        , "parentKey1"
        , "parentKey2"
        , "parentKey1.parentKey2.keyの値がオブジェクトではない"
    );
}
