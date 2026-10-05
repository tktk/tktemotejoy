#include "tktemotejoy/commandlineoptions.h"
#include "tktemotejoy/file.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/evdevstate.h"
#include "tktemotejoy/evdev.h"
#include "tktusbrepeater/tktusbrepeater.h"
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

    tktemotejoy::Mappings generateMappingsFromFile(
        const std::string &     _FILE_PATH
        , const std::size_t &   _BUTTONS
        , const std::size_t &   _AXES
    )
    {
        const auto  JSON_STRING = tktemotejoy::readFile( _FILE_PATH );

        const auto  JSON = tktemotejoy::parseCustomJson( JSON_STRING );

        return tktemotejoy::generateMappings(
            JSON
            , _BUTTONS
            , _AXES
        );
    }

    void initializeEvdevState(
        const int                               _DESCRIPTOR
        , const tktemotejoy::EvdevKeyIndices &  _KEY_INDICES
        , const tktemotejoy::EvdevAbsIndices &  _ABS_INDICES
        , tktemotejoy::EvdevState &             _evdevState
    )
    {
        const auto  KEY_STATES = tktemotejoy::generateEvdevKeyStates( _DESCRIPTOR );

        const auto  KEY_STATES_SIZE = KEY_STATES.size();
        for( auto i = std::size_t( 0 ) ; i < KEY_STATES_SIZE ; ++i ) {
            const auto &    INDEX = _KEY_INDICES.at( i );
            if( INDEX < 0 ) {
                continue;
            }

            _evdevState.setButtonState(
                INDEX
                , KEY_STATES.test( i ) == true ? 1 : 0
            );
        }

        const auto  ABS_DATA_ARRAY = tktemotejoy::generateEvdevAbsDataArray( _DESCRIPTOR );

        const auto  ABS_DATA_ARRAY_SIZE = ABS_DATA_ARRAY.size();
        for( auto i = std::size_t( 0 ) ; i < ABS_DATA_ARRAY_SIZE ; ++i ) {
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

    void repeatLoop(
        int &                                   _evdev
        , const tktemotejoy::EvdevKeyIndices &  _KEY_INDICES
        , const tktemotejoy::EvdevAbsIndices &  _ABS_INDICES
        , const std::size_t &                   _BUTTONS
        , const std::size_t &                   _AXES
        , tktemotejoy::Mappings &               _mappings
        , tktusbrepeater::Writer &              _toRepeater
    )
    {
        auto    evdevState = tktemotejoy::EvdevState(
            _BUTTONS
            , _AXES
        );

        initializeEvdevState(
            _evdev
            , _KEY_INDICES
            , _ABS_INDICES
            , evdevState
        );
        auto    prevPspState = tktemotejoy::PspState();

        auto    inputEvents = tktemotejoy::EvdevInputEvents();

        const auto  INPUT_EVENTS_BEGIN = inputEvents.cbegin();

        while( true ) {
            const auto  READ_EVENTS = tktemotejoy::readEvdevInputEvents(
                _evdev
                , inputEvents
            );

            std::for_each(
                INPUT_EVENTS_BEGIN
                , INPUT_EVENTS_BEGIN + READ_EVENTS
                , [
                    &_KEY_INDICES
                    , &_ABS_INDICES
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
                        const auto &    INDEX = _KEY_INDICES.at( EVENT_CODE );
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
                        const auto &    INDEX = _ABS_INDICES.at( EVENT_CODE );
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

            auto    pspState = tktemotejoy::PspState();
            _mappings.evdevStateToPspState(
                pspState
                , evdevState
            );

            pspState.runWhenDiff(
                prevPspState
                , [
                    &_toRepeater
                ]
                (
                    const tktemotejoy::PspState::Bits & _BITS
                )
                {
                    _toRepeater.write(
                        &_BITS
                        , sizeof( _BITS )
                    );
                }
            );

            prevPspState = pspState;
        }
    }

    void writeClearBit(
        tktusbrepeater::Writer &    _toRepeater
    )
    {
        const auto  CLEAR_BITS = tktemotejoy::PspState::Bits( tktemotejoy::PSPSTATE_BITS_DEFAULT );

        _toRepeater.write(
            &CLEAR_BITS
            , sizeof( CLEAR_BITS )
        );
    }
}

int main(
    const int           _ARGC
    , char * const *    _argv
)
{
    auto    options = tktemotejoy::CommandLineOptions();
    if( tktemotejoy::initializeCommandLineOptions(
        options
        , _ARGC
        , _argv
    ) == false ) {
        return 1;
    }

    int evdev;
    const auto  EVDEV_CLOSER = tktemotejoy::openEvdev(
        evdev
        , options.deviceFilePath
    );

    const auto  KEY_INDICES = tktemotejoy::generateEvdevKeyIndices( evdev );
    const auto  ABS_INDICES = tktemotejoy::generateEvdevAbsIndices( evdev );

    const auto  BUTTONS = countAvailableIndices( KEY_INDICES );
    const auto  AXES = countAvailableIndices( ABS_INDICES );

    auto    mappings = generateMappingsFromFile(
        options.mapFilePath
        , BUTTONS
        , AXES
    );

    auto    toRepeaterUnique = tktusbrepeater::newWriter(
        options.socketName
        , options.endpoint
    );
    if( toRepeaterUnique.get() == nullptr ) {
        throw std::runtime_error( "tktusbrepeater::newWriter()が失敗" );
    }
    auto &  toRepeater = *toRepeaterUnique;

    try {
        repeatLoop(
            evdev
            , KEY_INDICES
            , ABS_INDICES
            , BUTTONS
            , AXES
            , mappings
            , toRepeater
        );
    } catch( const std::runtime_error & _EX ) {
        writeClearBit( toRepeater );

        throw _EX;
    }

    return 0;
}
