#include "tktemotejoy/tousbhostfs.h"
#include "tktemotejoy/descriptorcloser.h"
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cstddef>
#include <sstream>
#include <stdexcept>

namespace {
    enum {
        JOY_MAGIC = 0x909accf0,
    };

    struct JoyEvent
    {
        alignas( 1 ) unsigned int   magic;
        alignas( 1 ) unsigned int   value;
    };

    struct DestroyAddrinfo
    {
        void operator()(
            addrinfo *  _addrinfo
        ) const
        {
            freeaddrinfo( _addrinfo );
        }
    };

    using AddrinfoDestroyer = std::unique_ptr<
        addrinfo
        , DestroyAddrinfo
    >;

    in_addr generateInAddr(
        const std::string &     _HOST
    )
    {
        auto    hints = addrinfo();
        std::memset(
            &hints
            , 0
            , sizeof( hints )
        );

        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        auto    results = static_cast< addrinfo * >( nullptr );

        if( getaddrinfo(
            _HOST.c_str()
            , nullptr
            , &hints
            , &results
        ) != 0 ) {
            auto    oStringStream = std::ostringstream();

            oStringStream << "getaddrinfo()が失敗 : " << '"' << _HOST << '"';

            throw std::runtime_error( oStringStream.str() );
        }

        auto    addrinfoDestroyer = AddrinfoDestroyer( results );

        const auto  IN_ADDR = reinterpret_cast< const sockaddr_in * >( results->ai_addr )->sin_addr;

        return IN_ADDR;
    }

    sockaddr_in generateSockaddrIn(
        const std::string &     _HOST
        , const unsigned short  _PORT
    )
    {
        const auto  IN_ADDR = generateInAddr( _HOST );

        auto    sockaddrIn = sockaddr_in();
        std::memset(
            &sockaddrIn
            , 0
            , sizeof( sockaddrIn )
        );

        sockaddrIn.sin_family = AF_INET;
        sockaddrIn.sin_port = htons( _PORT );
        sockaddrIn.sin_addr = IN_ADDR;

        return sockaddrIn;
    }
}

DescriptorCloser connectToUsbHostFs(
    int &                   _socket
    , const std::string &   _HOST
    , const unsigned short  _PORT
)
{
    const auto  SOCKADDR_IN = generateSockaddrIn(
        _HOST
        , _PORT
    );

    _socket = socket(
        PF_INET
        , SOCK_STREAM
        , 0
    );
    if( _socket < 0 ) {
        throw std::runtime_error( "socket()が失敗" );
    }

    auto    closer = DescriptorCloser( &_socket );

    if( connect(
        _socket
        , reinterpret_cast< const sockaddr * >( &SOCKADDR_IN )
        , sizeof( SOCKADDR_IN )
    ) < 0 ) {
        throw std::runtime_error( "connect()が失敗" );
    }

    auto    flag = 1;
    if( setsockopt(
        _socket
        , IPPROTO_TCP
        , TCP_NODELAY
        , &flag
        , sizeof( flag )
    ) < 0 ) {
        throw std::runtime_error( "setsockopt()が失敗" );
    }

    return closer;
}

void writeToUsbHostFs(
    const int               _SOCKET
    , const unsigned int    _DATA
)
{
    auto    joyEvent = JoyEvent{
        JOY_MAGIC,
        _DATA,
    };
    const auto  EVENT_LENGTH = sizeof( joyEvent );

    const auto  EVENT_HEAD = reinterpret_cast< const char * >( &joyEvent );

    auto    totalWritten = std::size_t( 0 );

    while( totalWritten < EVENT_LENGTH ) {
        const auto  WRITTEN = write(
            _SOCKET
            , EVENT_HEAD + totalWritten
            , EVENT_LENGTH - totalWritten
        );
        if( WRITTEN < 0 ) {
            throw std::runtime_error( "write()が失敗" );
        }

        totalWritten += WRITTEN;
    }
}
