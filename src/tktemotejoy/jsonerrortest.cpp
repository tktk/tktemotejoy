#include "tktemotejoy/test.h"
#include "tktemotejoy/jsonerror.h"

namespace {
    class JsonErrorTest : public ::testing::Test
    {
    public:
        template< typename JSON_ERROR_T >
        void test(
            const char *    _EXPECTED_WHAT
        ) const
        {
            const auto  ERROR = JSON_ERROR_T()();

            EXPECT_STREQ( _EXPECTED_WHAT, ERROR.what() );
        }
    };
}

TEST_F(
    JsonErrorTest
    , JsonError
)
{
    struct JsonError
    {
        auto operator()(
        ) const
        {
            return jsonError(
                "エラー"
                , "key1"
                , "key2"
                , "key3"
            );
        }
    };

    this->test< JsonError >( "key1.key2.key3がエラー" );
}

TEST_F(
    JsonErrorTest
    , JsonIsNotExists
)
{
    struct JsonIsNotExists
    {
        auto operator()(
        ) const
        {
            return jsonIsNotExists( "key" );
        }
    };

    this->test< JsonIsNotExists >( "keyが存在しない" );
}

//TODO JsonIsNotInteger
//TODO JsonIsNotUnsigned
//TODO JsonIsNotString
//TODO JsonIsNotArray
//TODO JsonIsNotObject
