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
                    , _ARGS.data()
                )
            );

            if( _EXPECTED_INITIALIZED == true ) {
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.mapFilePath, commandLineOptions.mapFilePath );
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.ip, commandLineOptions.ip );
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.port, commandLineOptions.port );
                EXPECT_EQ( _EXPECTED_COMMAND_LINE_OPTIONS.deviceFilePath, commandLineOptions.deviceFilePath );
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
            "-i",
            "IP",
            "-p",
            "10",
            "DEVICEFILEPATH",
        }
        , true
        , CommandLineOptions{
            "MAPFILEPATH",
            "DEVICEFILEPATH",
            "IP",
            10,
        }
    );
}

TEST_F(
    CommandLineOptions_initializeTest
    , NotExistsIp
)
{
    this->test(
        {
            "tktemotejoy",
            "-m",
            "MAPFILEPATH",
            "-p",
            "10",
            "DEVICEFILEPATH",
        }
        , true
        , CommandLineOptions{
            "MAPFILEPATH",
            "DEVICEFILEPATH",
            "localhost",
            10,
        }
    );
}

TEST_F(
    CommandLineOptions_initializeTest
    , NotExistsPort
)
{
    this->test(
        {
            "tktemotejoy",
            "-m",
            "MAPFILEPATH",
            "-i",
            "IP",
            "DEVICEFILEPATH",
        }
        , true
        , CommandLineOptions{
            "MAPFILEPATH",
            "DEVICEFILEPATH",
            "IP",
            10004,
        }
    );
}

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
