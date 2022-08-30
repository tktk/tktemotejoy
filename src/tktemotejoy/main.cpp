#include "tktemotejoy/commandlineoptions.h"
#include "tktemotejoy/file.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/joystickstate.h"
#include "tktemotejoy/tousbhostfs.h"
#include "tktemotejoy/joystick.h"
#include <string>
#include <cstddef>

namespace {
    Mappings generateMappingsFromFile(
        const std::string &     _FILE_PATH
        , const std::size_t &   _BUTTONS
        , const std::size_t &   _AXES
    )
    {
        const auto  JSON_STRING = readFile( _FILE_PATH );

        const auto  JSON = parseCustomJson( JSON_STRING );

        return generateMappings(
            JSON
            , _BUTTONS
            , _AXES
        );
    }
}

int main(
    const int           _ARGC
    , char * const *    _argv
)
{
    auto    options = CommandLineOptions();
    if( initializeCommandLineOptions(
        options
        , _ARGC
        , _argv
    ) == false ) {
        return 1;
    }

    int joystick;
    const auto  JOYSTICK_CLOSER = openJoystick(
        joystick
        , options.deviceFilePath
    );

    const auto  BUTTONS = getJoystickButtons( joystick );
    const auto  AXES = getJoystickAxes( joystick );

    auto    mappings = generateMappingsFromFile(
        options.mapFilePath
        , BUTTONS
        , AXES
    );

    int socket_;
    const auto  SOCKET_CLOSER = connectToUsbHostFs(
        socket_
        , options.ip
        , options.port
    );

    auto    joystickState = JoystickState(
        BUTTONS
        , AXES
    );

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

        auto    pspState = PspState();
        mappings.joystickStateToPspState(
            pspState
            , joystickState
        );

        if( ( TYPE & JS_EVENT_INIT ) == 0 ) {
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
        }

        prevPspState = pspState;
    }

    return 0;
}
