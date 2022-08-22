#include "tktemotejoy/test.h"
#include "tktemotejoy/commandlineoptions.h"
#include <vector>

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
    , NotExistsMapFilePath
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

//TODO NotExistsPort

TEST_F(
    CommandLineOptions_initializeTest
    , NotExistsDeviceFilePath
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

//TODO Help
