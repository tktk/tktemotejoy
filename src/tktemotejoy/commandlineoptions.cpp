#include "tktemotejoy/commandlineoptions.h"
#include <unistd.h>
#include <string>
#include <iostream>

namespace {
    enum {
        OPTION_KEY_MAP = 'm',
        OPTION_KEY_IP = 'i',
        OPTION_KEY_PORT = 'p',
        OPTION_KEY_HELP = 'h',
    };

    const auto  OPTION_DEFAULT_IP = std::string( "localhost" );
    const auto  OPTION_DEFAULT_PORT = 10004;

}

bool initializeCommandLineOptions(
    CommandLineOptions &    _commandLineOptions
    , const int             _ARGC
    , const char * const *  _ARGV
)
{
    _commandLineOptions.ip = OPTION_DEFAULT_IP;
    _commandLineOptions.port = OPTION_DEFAULT_PORT;

    auto    existsMapFilePath = false;
    auto    existsDeviceFilePath = false;

    auto    printHelp = false;

    auto    argv = const_cast< char * const * >( _ARGV );
    while( true ) {
        const auto  OPTION_KEY = getopt(
            _ARGC
            , argv
            , "m:i:p:h"
        );
        if( OPTION_KEY < 0 ) {
            break;
        }

        switch( OPTION_KEY ) {
        case OPTION_KEY_MAP:
            existsMapFilePath = true;
            _commandLineOptions.mapFilePath = std::string( optarg );
            break;

        case OPTION_KEY_IP:
            _commandLineOptions.ip = std::string( optarg );
            break;

        case OPTION_KEY_PORT:
            _commandLineOptions.port = std::stoul( optarg );
            break;

        case OPTION_KEY_HELP:
            printHelp = true;
            goto LOOP_END;
            break;

        default:
            printHelp = true;
            goto LOOP_END;
            break;
        }
    }
    LOOP_END:

    if( _ARGC - optind >= 1 ) {
        existsDeviceFilePath = true;
        _commandLineOptions.deviceFilePath = std::string( _ARGV[ optind ] );
    }

    if( printHelp == false ) {
        if( existsMapFilePath == false ) {
            std::cerr << "マッピングファイルの指定が必要" << std::endl;

            printHelp = true;
        }
        if( existsDeviceFilePath == false ) {
            std::cerr << "ゲームパッドのデバイスファイルの指定が必要" << std::endl;

            printHelp = true;
        }
    }

    if( printHelp == true ) {
        std::cerr << "使い方: " << _ARGV[ 0 ] << " [オプション]... デバイスファイル" << std::endl;
        std::cerr << "オプション:" << std::endl;
        std::cerr << "-m map    : マッピングファイル" << std::endl;
        std::cerr << "-i ip     : usbhostfs_pcのホスト (初期値:" << OPTION_DEFAULT_IP << ')' << std::endl;
        std::cerr << "-p port   : usbhostfs_pcのポート番号 (初期値:" << OPTION_DEFAULT_PORT << ')' << std::endl;
        std::cerr << "-h        : ヘルプ" << std::endl;

        return false;
    }

    return true;
}
