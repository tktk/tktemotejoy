#include "tktemotejoy/test.h"
#include "tktemotejoy/jsonerror.h"

TEST(
    JsonErrorTest
    , Standard
)
{
    const auto  ERROR = jsonError(
        "エラー"
        , "key1"
        , "key2"
        , "key3"
    );

    EXPECT_STREQ( "key1.key2.key3がエラー", ERROR.what() );
}
