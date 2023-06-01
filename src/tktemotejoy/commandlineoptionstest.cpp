#include "tktemotejoy/test.h"
#include "tktemotejoy/commandlineoptions.h"
#include <vector>
#include <unistd.h>

namespace {
    class CommandLineOptions_initializeTest : public ::testing::Test
    {
    public:
        void test(
            const std::vector< const char * > & _ARGS
            , const bool                        _EXPECTED_INITIALIZED
            , CommandLineOptions                _EXPECTED_COMMAND_LINE_OPTIONS
        ) const
        {
            auto    commandLineOptions = CommandLineOptions();

            optind = 1;

            EXPECT_EQ(
                _EXPECTED_INITIALIZED
                , initializeCommandLineOptions(
                    commandLineOptions
                    , _ARGS.size()
                    , const_cast< char * const * >( _ARGS.data() )
                )
            );

            if( _EXPECTED_INITIALIZED == true ) {
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.mapFilePath, commandLineOptions.mapFilePath );
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.deviceFilePath, commandLineOptions.deviceFilePath );
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.socketName, commandLineOptions.socketName );
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.endpoint, commandLineOptions.endpoint );
            }
        }
    };
}

TEST_F(
    CommandLineOptions_initializeTest
    , Standard
)
{
    this->test(
        {
            "tktemotejoy",
            "-m",
            "MAPFILEPATH",
            "-s",
            "SOCKET_NAME",
            "-e",
            "8a",
            "DEVICEFILEPATH",
        }
        , true
        , CommandLineOptions{
            "MAPFILEPATH",
            "DEVICEFILEPATH",
            "SOCKET_NAME",
            0x8a,
        }
    );
}

/*
TEST_F(
    CommandLineOptions_initializeTest
    , Help
)
{
    this->test(
        {
            "tktemotejoy",
            "-m",
            "MAPFILEPATH",
            "-i",
            "IP",
            "-p",
            "10",
            "DEVICEFILEPATH",
            "-h",
        }
        , false
        , CommandLineOptions{}
    );
}

//TODO FailedNotExistsSocketName
//TODO FailedNotExistsEndpoint

TEST_F(
    CommandLineOptions_initializeTest
    , FailedNotExistsMapFilePath
)
{
    this->test(
        {
            "tktemotejoy",
            "-i",
            "IP",
            "-p",
            "10",
            "DEVICEFILEPATH",
        }
        , false
        , CommandLineOptions{}
    );
}

TEST_F(
    CommandLineOptions_initializeTest
    , FailedNotExistsDeviceFilePath
)
{
    this->test(
        {
            "tktemotejoy",
            "-m",
            "MAPFILEPATH",
            "-i",
            "IP",
            "-p",
            "10",
        }
        , false
        , CommandLineOptions{}
    );
}

TEST_F(
    CommandLineOptions_initializeTest
    , FailedContainsIllegalOption
)
{
    this->test(
        {
            "tktemotejoy",
            "-m",
            "MAPFILEPATH",
            "-i",
            "IP",
            "-p",
            "10",
            "-X",
            "DEVICEFILEPATH",
        }
        , false
        , CommandLineOptions{}
    );
}
*/
