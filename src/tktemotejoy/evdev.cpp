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

EvdevAxisStates generateEvdevAxisStates(
    const int   _DESCRIPTOR
)
{
    //TODO
    return EvdevAxisStates();
}

EvdevInputEvents::size_type readEvdevInputEvents(
    const int               _DESCRIPTOR
    , EvdevInputEvents &    _inputEvents
)
{
    //TODO
    return 0;
}
