#include "tktemotejoy/evdev.h"
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#include <stdexcept>

DescriptorCloser openEvdev(
    int &                   _descriptor
    , const std::string &   _DEVICE_PATH
)
{
    _descriptor = open(
        _DEVICE_PATH.c_str()
        , O_RDONLY
    );
    if( _descriptor < 0 ) {
        auto    oStringStream = std::ostringstream();

        oStringStream << "open()が失敗 : " << '"' << _DEVICE_PATH << '"';

        throw std::runtime_error( oStringStream.str() );
    }

    return DescriptorCloser( &_descriptor );
}

EvdevKeyStates generateEvdevKeyStates(
    const int   _DESCRIPTOR
)
{
    auto    keyStates = EvdevKeyStates();

    ioctl(
        _DESCRIPTOR
        , EVIOCGKEY( sizeof( keyStates ) )
        , &keyStates
    );

    return keyStates;
}

EvdevAbsDataArray generateEvdevAbsDataArray(
    const int   _DESCRIPTOR
)
{
    auto    absDataArray = EvdevAbsDataArray();

    const auto  SIZE = absDataArray.size();
    for( auto i = EvdevAbsDataArray::size_type( 0 ) ; i < SIZE ; i++ ) {
        ioctl(
            _DESCRIPTOR
            , EVIOCGABS( i )
            , &( absDataArray.at( i ) )
        );
    }

    return absDataArray;
}

EvdevInputEvents::size_type readEvdevInputEvents(
    const int               _DESCRIPTOR
    , EvdevInputEvents &    _inputEvents
)
{
    const auto  READ_SIZE = read(
        _DESCRIPTOR
        , _inputEvents.data()
        , sizeof( _inputEvents )
    );
    if( READ_SIZE < 0 ) {
        throw std::runtime_error( "read()が失敗" );
    }

    const auto  READ_INPUT_EVENTS_COUNT = READ_SIZE / sizeof( EvdevInputEvents::value_type );

    return READ_INPUT_EVENTS_COUNT;
}
