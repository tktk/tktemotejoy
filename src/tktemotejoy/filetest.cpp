#include "tktemotejoy/test.h"
#include "tktemotejoy/file.h"
#include <string>
#include <sstream>

namespace {
    const auto  DUMMY_PATH = std::string( "DUMMY_PATH" );
    const auto  TEST_CONTENTS = std::string( "TEST_CONTENTS" );

    struct GenerateDummyStream
    {
        auto operator()(
            const std::string &
        ) const
        {
            return std::istringstream( TEST_CONTENTS );
        }
    };
}

TEST(
    ReadFileTest
    , Standard
)
{
    EXPECT_EQ( TEST_CONTENTS, readFile< GenerateDummyStream >( DUMMY_PATH ) );
}

//TODO
/*
TEST(
    ReadFileTest
    , NotFound
)
{
    EXPECT_ANY_THROW( readFile( "notfound" ) );
}
*/
