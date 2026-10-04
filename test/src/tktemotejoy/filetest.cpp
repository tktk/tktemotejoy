#include "tktemotejoy/test.h"
#include "tktemotejoy/file.h"
#include <ios>
#include <string>
#include <sstream>

namespace {
    const auto  DUMMY_PATH = std::string( "DUMMY_PATH" );
    const auto  TEST_CONTENTS = std::string( "TEST_CONTENTS" );
}

TEST(
    ReadFileTest
    , Standard
)
{
    struct GenerateDummyStream
    {
        auto operator()(
            const std::string &
        ) const
        {
            return std::istringstream( TEST_CONTENTS );
        }
    };

    EXPECT_EQ( TEST_CONTENTS, tktemotejoy::readFile< GenerateDummyStream >( DUMMY_PATH ) );
}

TEST(
    ReadFileTest
    , Failed
)
{
    struct GenerateDummyStreamForFailed
    {
        auto operator()(
            const std::string &
        ) const
        {
            auto    stream = std::istringstream();
            stream.setstate( std::ios::badbit );

            return stream;
        }
    };

    EXPECT_ANY_THROW( tktemotejoy::readFile< GenerateDummyStreamForFailed >( DUMMY_PATH ) );
}
