#include "tktemotejoy/commandlineoptions.h"
#include "tktemotejoy/file.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/joystickstate.h"
#include "tktemotejoy/tousbhostfs.h"
#include "tktemotejoy/joystick.h"
#include <string>
#include <iostream>

namespace {
    Mappings generateMappingsFromFile(
        const std::string & _FILE_PATH
    )
    {
        const auto  JSON_STRING = readFile( _FILE_PATH );

        const auto  JSON = parseCustomJson( JSON_STRING );

        return generateMappings( JSON );
    }

    JoystickState generateJoystickState(
        const int   _DESCRIPTOR
    )
    {
        const auto  BUTTONS = getJoystickButtons( _DESCRIPTOR );
        const auto  AXES = getJoystickAxes( _DESCRIPTOR );

        return JoystickState(
            BUTTONS
            , AXES
        );
    }
}

int main(
    const int       _ARGC
    , const char ** _ARGV
)
{
    auto    options = CommandLineOptions();
    if( initializeCommandLineOptions(
        options
        , _ARGC
        , _ARGV
    ) == false ) {
        return 1;
    }

    auto    mappings = generateMappingsFromFile( options.mapFilePath );

    int socket_;
    const auto  SOCKET_CLOSER = connectToUsbHostFs(
        socket_
        , options.ip
        , options.port
    );

    int joystick;
    const auto  JOYSTICK_CLOSER = openJoystick(
        joystick
        , options.deviceFilePath
    );

    auto    joystickState = generateJoystickState( joystick );

    auto    prevPspState = PspState();

    auto    jsEvent = js_event();
    while( true ) {
        readJoystick(
            joystick
            , jsEvent
        );

        const auto &    TYPE = jsEvent.type;

        const auto &    INDEX = jsEvent.number;
        const auto &    VALUE = jsEvent.value;

        if( ( TYPE & JS_EVENT_BUTTON ) != 0 ) {
            joystickState.setButtonState(
                INDEX
                , VALUE
            );
        } else if( ( TYPE & JS_EVENT_AXIS ) != 0 ) {
            joystickState.setAxisState(
                INDEX
                , VALUE
            );
        }

        if( ( TYPE & JS_EVENT_INIT ) != 0 ) {
            continue;
        }

        auto    pspState = PspState();
        mappings.joystickStateToPspState(
            pspState
            , joystickState
        );

        pspState.diff(
            prevPspState
            , [
                &socket_
            ]
            (
                const PspState::Bits &  _BITS
            )
            {
                writeToUsbHostFs(
                    socket_
                    , _BITS
                );
            }
        );

        prevPspState = pspState;
    }

    return 0;
}
