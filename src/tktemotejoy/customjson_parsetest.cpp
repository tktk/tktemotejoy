#include "tktemotejoy/test.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <vector>

namespace {
    class ParseCustomJsonTest : public ::testing::Test
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
    };
}

TEST_F(
    ParseCustomJsonTest
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
    ParseCustomJsonTest
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

//TODO ObjectWithTailComma
//TODO WithComment
