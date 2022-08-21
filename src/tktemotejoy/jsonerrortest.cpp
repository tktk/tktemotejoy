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
                "がエラー"
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

TEST_F(
    JsonErrorTest
    , JsonIsNotInteger
)
{
    struct JsonIsNotInteger
    {
        auto operator()(
        ) const
        {
            return jsonIsNotInteger( "key" );
        }
    };

    this->test< JsonIsNotInteger >( "keyの値が整数ではない" );
}

TEST_F(
    JsonErrorTest
    , JsonIsNotUnsigned
)
{
    struct JsonIsNotUnsigned
    {
        auto operator()(
        ) const
        {
            return jsonIsNotUnsigned( "key" );
        }
    };

    this->test< JsonIsNotUnsigned >( "keyの値が符号なし整数ではない" );
}

TEST_F(
    JsonErrorTest
    , JsonIsNotString
)
{
    struct JsonIsNotString
    {
        auto operator()(
        ) const
        {
            return jsonIsNotString( "key" );
        }
    };

    this->test< JsonIsNotString >( "keyの値が文字列ではない" );
}

TEST_F(
    JsonErrorTest
    , JsonIsNotArray
)
{
    struct JsonIsNotArray
    {
        auto operator()(
        ) const
        {
            return jsonIsNotArray( "key" );
        }
    };

    this->test< JsonIsNotArray >( "keyの値が配列ではない" );
}

TEST_F(
    JsonErrorTest
    , JsonIsNotObject
)
{
    struct JsonIsNotObject
    {
        auto operator()(
        ) const
        {
            return jsonIsNotObject( "key" );
        }
    };

    this->test< JsonIsNotObject >( "keyの値がオブジェクトではない" );
}
