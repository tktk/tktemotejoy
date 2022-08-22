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

//TODO NotFound
