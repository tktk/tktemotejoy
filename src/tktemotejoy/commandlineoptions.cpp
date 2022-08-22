#include "tktemotejoy/commandlineoptions.h"
#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include <typeinfo>

namespace {
    const auto  OPTION = "オプション";

    using OptionTypeMap = std::string;
    const auto  OPTION_KEY_MAP = "map";
    const auto  OPTION_NAME_MAP = "map,m";
    const auto  OPTION_DESCRIPTION_MAP = "マッピングファイル";

    using OptionTypeDevice = std::string;
    const auto  OPTION_KEY_DEVICE = "device";
    const auto  OPTION_NAME_DEVICE = "device,d";
    const auto  OPTION_DESCRIPTION_DEVICE = "ゲームパッドのデバイスファイル";

    using OptionTypeIp = std::string;
    const auto  OPTION_KEY_IP = "ip";
    const auto  OPTION_NAME_IP = "ip,i";
    const auto  OPTION_DESCRIPTION_IP = "usbhostfs_pcのホスト";
    const auto  OPTION_DEFAULT_IP = std::string( "localhost" );

    using OptionTypePort = unsigned short;
    const auto  OPTION_KEY_PORT = "port";
    const auto  OPTION_NAME_PORT = "port,p";
    const auto  OPTION_DESCRIPTION_PORT = "usbhostfs_pcのポート番号";
    const auto  OPTION_DEFAULT_PORT = 10004;

/*
    const auto  OPTION_KEY_HELP = "help";
    const auto  OPTION_NAME_HELP = "help";
    const auto  OPTION_DESCRIPTION_HELP = "ヘルプ";
*/
}

bool initializeCommandLineOptions(
    CommandLineOptions &    _commandLineOptions
    , const int             _ARGC
    , const char * const *  _ARGV
)
{
    namespace options = boost::program_options;

    auto    optionsDescription = options::options_description( OPTION );

    optionsDescription.add_options()
        (
            OPTION_NAME_MAP
            , options::value< OptionTypeMap >()->value_name( OPTION_KEY_MAP )
            , OPTION_DESCRIPTION_MAP
        )
        (
            OPTION_NAME_DEVICE
            , options::value< OptionTypeDevice >()->value_name( OPTION_KEY_DEVICE )
            , OPTION_DESCRIPTION_DEVICE
        )
        (
            OPTION_NAME_IP
            , options::value< OptionTypeIp >()->value_name( OPTION_KEY_IP )->default_value( OPTION_DEFAULT_IP )
            , OPTION_DESCRIPTION_IP
        )
        (
            OPTION_NAME_PORT
            , options::value< OptionTypePort >()->value_name( OPTION_KEY_PORT )->default_value( OPTION_DEFAULT_PORT )
            , OPTION_DESCRIPTION_PORT
        )
/*
        (
            OPTION_NAME_HELP
            , OPTION_DESCRIPTION_HELP
        )
*/
    ;

    auto    positionalOptionsDescription = options::positional_options_description();
    positionalOptionsDescription.add(
        OPTION_KEY_DEVICE
        , -1
    );

    auto    variablesMap = options::variables_map();
    options::store(
        options::command_line_parser(
            _ARGC
            , _ARGV
        )
            .options( optionsDescription )
            .positional( positionalOptionsDescription )
            .run()
        , variablesMap
    );
    options::notify( variablesMap );

    auto    printHelp = false;

/*
    if( variablesMap.count( OPTION_NAME_HELP ) > 0 ) {
        std::cout << optionsDescription << std::endl;

        return 0;
    }
*/
    if( variablesMap.count( OPTION_KEY_MAP ) <= 0 ) {
        std::cout << OPTION_DESCRIPTION_MAP << "の指定が必要" << std::endl;

        printHelp = true;
    }
    if( variablesMap.count( OPTION_KEY_DEVICE ) <= 0 ) {
        std::cout << OPTION_DESCRIPTION_DEVICE << "の指定が必要" << std::endl;

        printHelp = true;
    }

    if( printHelp == true ) {
        std::cout << optionsDescription << std::endl;

        return false;
    }

    _commandLineOptions.mapFilePath = variablesMap[ OPTION_KEY_MAP ].as< OptionTypeMap >();
    _commandLineOptions.deviceFilePath = variablesMap[ OPTION_KEY_DEVICE ].as< OptionTypeDevice >();
    _commandLineOptions.ip = variablesMap[ OPTION_KEY_IP ].as< OptionTypeIp >();
    _commandLineOptions.port = variablesMap[ OPTION_KEY_PORT ].as< OptionTypePort >();

    return true;
}
