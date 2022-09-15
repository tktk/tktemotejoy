#include "tktemotejoy/commandlineoptions.h"
#include "tktemotejoy/file.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/evdevstate.h"
#include "tktemotejoy/tousbhostfs.h"
#include "tktemotejoy/evdev.h"
#include <string>
#include <algorithm>
#include <cstddef>
#include <linux/input.h>

namespace {
    template< typename INDICES_T >
    std::size_t countAvailableIndices(
        const INDICES_T &   _INDICES
    )
    {
        return std::count_if(
            _INDICES.begin()
            , _INDICES.end()
            , [](
                const int & _INDEX
            ) -> bool
            {
                return _INDEX >= 0;
            }
        );
    }

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

    void initializeEvdevState(
        const int                   _DESCRIPTOR
        , const EvdevKeyIndices &   _KEY_INDICES
        , const EvdevAbsIndices &   _ABS_INDICES
        , EvdevState &              _evdevState
    )
    {
        const auto  KEY_STATES = generateEvdevKeyStates( _DESCRIPTOR );

        const auto  KEY_STATES_SIZE = KEY_STATES.size();
        for( auto i = std::size_t( 0 ) ; i < KEY_STATES_SIZE ; i++ ) {
            const auto &    INDEX = _KEY_INDICES.at( i );
            if( INDEX < 0 ) {
                continue;
            }

            _evdevState.setButtonState(
                INDEX
                , KEY_STATES.test( i ) == true ? 1 : 0
            );
        }

        const auto  ABS_DATA_ARRAY = generateEvdevAbsDataArray( _DESCRIPTOR );

        const auto  ABS_DATA_ARRAY_SIZE = ABS_DATA_ARRAY.size();
        for( auto i = std::size_t( 0 ) ; i < ABS_DATA_ARRAY_SIZE ; i++ ) {
            const auto &    INDEX = _ABS_INDICES.at( i );
            if( INDEX < 0 ) {
                continue;
            }

            _evdevState.setAxisState(
                INDEX
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

    int evdev;
    const auto  EVDEV_CLOSER = openEvdev(
        evdev
        , options.deviceFilePath
    );

    const auto  KEY_INDICES = generateEvdevKeyIndices( evdev );
    const auto  ABS_INDICES = generateEvdevAbsIndices( evdev );

    const auto  BUTTONS = countAvailableIndices( KEY_INDICES );
    const auto  AXES = countAvailableIndices( ABS_INDICES );

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

    auto    evdevState = EvdevState(
        BUTTONS
        , AXES
    );

    initializeEvdevState(
        evdev
        , KEY_INDICES
        , ABS_INDICES
        , evdevState
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
                &KEY_INDICES
                , &ABS_INDICES
                , &evdevState
            ]
            (
                const input_event & _EVENT
            )
            {
                const auto &    EVENT_TYPE = _EVENT.type;
                const auto &    EVENT_CODE = _EVENT.code;
                const auto &    EVENT_VALUE = _EVENT.value;

                if( EVENT_TYPE == EV_KEY ) {
                    const auto &    INDEX = KEY_INDICES.at( EVENT_CODE );
                    if( INDEX < 0 ) {
                        auto    oStringStream = std::ostringstream();

                        oStringStream << "無効なキーコード : [" << EVENT_CODE << ']';

                        throw std::runtime_error( oStringStream.str() );
                    }

                    evdevState.setButtonState(
                        INDEX
                        , EVENT_VALUE
                    );
                } else if( EVENT_TYPE == EV_ABS ) {
                    const auto &    INDEX = ABS_INDICES.at( EVENT_CODE );
                    if( INDEX < 0 ) {
                        auto    oStringStream = std::ostringstream();

                        oStringStream << "無効な軸コード : [" << EVENT_CODE << ']';

                        throw std::runtime_error( oStringStream.str() );
                    }

                    evdevState.setAxisState(
                        INDEX
                        , EVENT_VALUE
                    );
                }
            }
        );

        auto    pspState = PspState();
        mappings.evdevStateToPspState(
            pspState
            , evdevState
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
