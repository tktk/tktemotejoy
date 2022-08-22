#include "tktemotejoy/test.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <vector>
#include <map>

namespace {
    class CustomJson_parseTest : public ::testing::Test
    {
    public:
        void testArray(
            const std::string &                     _CUSTOM_JSON
            , const std::vector< std::string > &    _EXPECTED_STRINGS
        ) const
        {
            const auto  JSON = parseCustomJson( _CUSTOM_JSON );

            ASSERT_TRUE( JSON.is_array() );

            const auto &    ARRAY = JSON.get_ref< const Json::array_t & >();

            ASSERT_EQ( _EXPECTED_STRINGS.size(), ARRAY.size() );

            auto    index = std::size_t( 0 );
            for( const auto & J : ARRAY ) {
                ASSERT_TRUE( J.is_string() );

                EXPECT_EQ( _EXPECTED_STRINGS.at( index ), J.get_ref< const Json::string_t & >() );

                index++;
            }
        }

        void testObject(
            const std::string &                             _CUSTOM_JSON
            , const std::map< std::string, std::string > &  _EXPECTED_MAP
        ) const
        {
            const auto  JSON = parseCustomJson( _CUSTOM_JSON );

            ASSERT_TRUE( JSON.is_object() );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            ASSERT_EQ( _EXPECTED_MAP.size(), OBJECT.size() );

            for( const auto & ITEM : OBJECT ) {
                const auto &    J = ITEM.second;

                ASSERT_TRUE( J.is_string() );

                const auto  IT = _EXPECTED_MAP.find( ITEM.first );
                ASSERT_NE( _EXPECTED_MAP.end(), IT );

                EXPECT_EQ( IT->second, J.get_ref< const Json::string_t & >() );
            }
        }
    };
}

TEST_F(
    CustomJson_parseTest
    , Standard
)
{
    this->testArray(
        R"([
    "abc",
    "def",
    "ghi"
])"
        , {
            "abc"
            , "def"
            , "ghi"
        }
    );
}

TEST_F(
    CustomJson_parseTest
    , ArrayWithTailComma
)
{
    this->testArray(
        R"([
    "jkl",
    "mno",
    "pqr",
])"
        , {
            "jkl"
            , "mno"
            , "pqr"
        }
    );
}

TEST_F(
    CustomJson_parseTest
    , ObjectWithTailComma
)
{
    this->testObject(
        R"({
    "key1" : "abc",
    "key2" : "def",
    "key3" : "ghi",
})"
        , {
            { "key1", "abc" },
            { "key2", "def" },
            { "key3", "ghi" },
        }
    );
}

TEST_F(
    CustomJson_parseTest
    , WithLineComment
)
{
    this->testArray(
        R"([    //コメント
    "abc",
    "def",
    "ghi"
])"
        , {
            "abc"
            , "def"
            , "ghi"
        }
    );
}

TEST_F(
    CustomJson_parseTest
    , WithBlockComment
)
{
    this->testArray(
        R"([
    "abc",
/*
    "def",
*/
    "ghi",
/*
    "jkl",
*/
    "mno"
])"
        , {
            "abc"
            , "ghi"
            , "mno"
        }
    );
}

TEST_F(
    CustomJson_parseTest
    , WithLineCommentAndBlockComment
)
{
    this->testArray(
        R"([
    "abc",
///*
    "def",
//*/
    "ghi"
])"
        , {
            "abc"
            , "def"
            , "ghi"
        }
    );
}
