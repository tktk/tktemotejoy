#include "tktemotejoy/joystick.h"
#include "tktemotejoy/descriptorcloser.h"
#include <linux/joystick.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#include <stdexcept>

DescriptorCloser openJoystick(
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

unsigned char getJoystickButtons(
    const int   _DESCRIPTOR
)
{
    unsigned char   buttons;

	if( ioctl(
        _DESCRIPTOR
        , JSIOCGBUTTONS
        , &buttons
    ) < 0 ) {
        throw std::runtime_error( "ioctl()が失敗 : JSIOCGBUTTONS" );
    }

    return buttons;
}

unsigned char getJoystickAxes(
    const int   _DESCRIPTOR
)
{
    unsigned char   axes;

	if( ioctl(
        _DESCRIPTOR
        , JSIOCGAXES
        , &axes
    ) < 0 ) {
        throw std::runtime_error( "ioctl()が失敗 : JSIOCGAXES" );
    }

    return axes;
}

void readJoystick(
    const int       _DESCRIPTOR
    , js_event &    _jsEvent
)
{
    if( read(
        _DESCRIPTOR
        , &_jsEvent
        , sizeof( _jsEvent )
    ) < 0 ) {
        throw std::runtime_error( "read()が失敗" );
    }
}
