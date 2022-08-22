#include "tktemotejoy/test.h"
#include "tktemotejoy/file.h"

TEST(
    ReadFileTest
    , Standard
)
{
    EXPECT_EQ(
        "TESTFILE"
        , readFile( "filetest/test.txt" )
    );
}

TEST(
    ReadFileTest
    , NotFound
)
{
    EXPECT_ANY_THROW( readFile( "notfound" ) );
}
