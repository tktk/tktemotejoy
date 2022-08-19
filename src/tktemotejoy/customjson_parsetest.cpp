#include "tktemotejoy/test.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <vector>
#include <sstream>

namespace {
    class ParseCustomJsonTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &                     _CUSTOM_JSON
            , const std::vector< std::string > &    _EXPECTED_STRINGS
        ) const
        {
            auto    iStringStream = std::istringstream( _CUSTOM_JSON );

            const auto  JSON = parseCustomJson( iStringStream );

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
    this->test(
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

//TODO WithTailComma
//TODO WithComment
