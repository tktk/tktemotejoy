#include "tktemotejoy/commandlineoptions.h"
#include "tktemotejoy/file.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/joystickstate.h"
#include "tktemotejoy/tousbhostfs.h"
#include "tktemotejoy/evdev.h"
#include <string>
#include <algorithm>
#include <cstddef>
#include <linux/input.h>

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

    void initializeJoystickState(
        const int           _DESCRIPTOR
        , JoystickState &   _joystickState
    )
    {
        const auto  KEY_STATES = generateEvdevKeyStates( _DESCRIPTOR );

        const auto  KEY_STATES_SIZE = KEY_STATES.size();
        for( auto i = std::size_t( 0 ) ; i < KEY_STATES_SIZE ; i++ ) {
            _joystickState.setButtonState(
                i
                , KEY_STATES.test( i ) == true ? 1 : 0
            );
        }

        const auto  ABS_DATA_ARRAY = generateEvdevAbsDataArray( _DESCRIPTOR );

        const auto  ABS_DATA_ARRAY_SIZE = ABS_DATA_ARRAY.size();
        for( auto i = std::size_t( 0 ) ; i < ABS_DATA_ARRAY_SIZE ; i++ ) {
            _joystickState.setAxisState(
                i
                , ABS_DATA_ARRAY.at( i ).value
            );
        }
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

    const auto  BUTTONS = EVDEV_BUTTONS;
    const auto  AXES = EVDEV_AXES;

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

    int evdev;
    const auto  JOYSTICK_CLOSER = openEvdev(
        evdev
        , options.deviceFilePath
    );

    auto    joystickState = JoystickState(
        BUTTONS
        , AXES
    );

    initializeJoystickState(
        evdev
        , joystickState
    );

    auto    prevPspState = PspState();

    auto    inputEvents = EvdevInputEvents();

    const auto  INPUT_EVENTS_BEGIN = inputEvents.cbegin();

    while( true ) {
        const auto  READ_EVENTS = readEvdevInputEvents(
            evdev
            , inputEvents
        );

        std::for_each(
            INPUT_EVENTS_BEGIN
            , INPUT_EVENTS_BEGIN + READ_EVENTS
            , [
                &joystickState
            ]
            (
                const input_event & _EVENT
            )
            {
                const auto &    EVENT_TYPE = _EVENT.type;
                const auto &    EVENT_CODE = _EVENT.code;
                const auto &    EVENT_VALUE = _EVENT.value;

                if( EVENT_TYPE == EV_KEY ) {
                    joystickState.setButtonState(
                        EVENT_CODE
                        , EVENT_VALUE
                    );
                } else if( EVENT_TYPE == EV_ABS ) {
                    joystickState.setAxisState(
                        EVENT_CODE
                        , EVENT_VALUE
                    );
                }
            }
        );

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
