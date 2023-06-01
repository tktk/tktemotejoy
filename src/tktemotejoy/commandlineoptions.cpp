#include "tktemotejoy/commandlineoptions.h"
#include <unistd.h>
#include <string>
#include <iostream>

namespace {
    enum {
        OPTION_KEY_MAP = 'm',
        OPTION_KEY_SOCKET_NAME = 's',
        OPTION_KEY_ENDPOINT = 'e',
        OPTION_KEY_HELP = 'h',
    };

    template< typename NUMBER_T >
    bool hexStringToInt(
        NUMBER_T &      _result
        , const char *  _STRING
    )
    {
        auto    index = std::size_t( 0 );

        const auto  RESULT = std::stoul(
            _STRING
            , &index
            , 16
        );
        if( _STRING[ index ] != '\0' ) {
            return false;
        }

        _result = RESULT;

        return true;
    }
}

bool initializeCommandLineOptions(
    CommandLineOptions &    _commandLineOptions
    , const int             _ARGC
    , char * const *        _argv
)
{
    auto    existsMapFilePath = false;
    auto    existsSocketName = false;
    auto    existsEndpoint = false;
    auto    existsDeviceFilePath = false;

    auto    illegalEndpoint = false;

    auto    printHelp = false;

    while( true ) {
        const auto  OPTION_KEY = getopt(
            _ARGC
            , _argv
            , "m:s:e:h"
        );
        if( OPTION_KEY < 0 ) {
            break;
        }

        switch( OPTION_KEY ) {
        case OPTION_KEY_MAP:
            existsMapFilePath = true;
            _commandLineOptions.mapFilePath = std::string( optarg );
            break;

        case OPTION_KEY_SOCKET_NAME:
            existsSocketName = true;
            _commandLineOptions.socketName = std::string( optarg );
            break;

        case OPTION_KEY_ENDPOINT:
            existsEndpoint = true;
            if( hexStringToInt(
                _commandLineOptions.endpoint
                , optarg
            ) == false ) {
                illegalEndpoint = true;
            }
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
        _commandLineOptions.deviceFilePath = std::string( _argv[ optind ] );
    }

    if( printHelp == false ) {
        if( existsMapFilePath == false ) {
            std::cerr << "マッピングファイルパスの指定が必要" << std::endl;

            printHelp = true;
        }
        if( existsSocketName == false ) {
            std::cerr << "接続先ソケット名の指定が必要" << std::endl;

            printHelp = true;
        }
        if( existsEndpoint == false ) {
            std::cerr << "接続先エンドポイントの指定が必要" << std::endl;

            printHelp = true;
        }
        if( existsDeviceFilePath == false ) {
            std::cerr << "ゲームパッドのデバイスファイルパスの指定が必要" << std::endl;

            printHelp = true;
        }
    }

    if( printHelp == false ) {
        if( illegalEndpoint == true ) {
            std::cerr << "接続先エンドポイントが不正" << std::endl;

            printHelp = true;
        }
    }

    if( printHelp == true ) {
        std::cerr << "使い方: " << _argv[ 0 ] << " [オプション]... デバイスファイルパス" << std::endl;
        std::cerr << "オプション:" << std::endl;
        std::cerr << "-m path   : マッピングファイルパス" << std::endl;
        std::cerr << "-s name   : 接続先ソケット名" << std::endl;
        std::cerr << "-e hex    : 接続先エンドポイント (16進数で指定)" << std::endl;
        std::cerr << "-h        : ヘルプ" << std::endl;

        return false;
    }

    return true;
}
