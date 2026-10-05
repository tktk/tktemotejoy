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

    void initializeEvdevStateAllKey(
        tktemotejoy::EvdevState &               _evdevState
        , const int &                           _EVDEV
        , const tktemotejoy::EvdevKeyIndices &  _KEY_INDICES
    )
    {
        const auto  KEY_STATES = tktemotejoy::generateEvdevKeyStates( _EVDEV );

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
    }

    void initializeEvdevStateAllAbs(
        tktemotejoy::EvdevState &               _evdevState
        , const int &                           _EVDEV
        , const tktemotejoy::EvdevAbsIndices &  _ABS_INDICES
    )
    {
        const auto  ABS_DATA_ARRAY = tktemotejoy::generateEvdevAbsDataArray( _EVDEV );

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

    void initializeEvdevState(
        tktemotejoy::EvdevState &               _evdevState
        , const int &                           _EVDEV
        , const tktemotejoy::EvdevKeyIndices &  _KEY_INDICES
        , const tktemotejoy::EvdevAbsIndices &  _ABS_INDICES
    )
    {
        initializeEvdevStateAllKey(
            _evdevState
            , _EVDEV
            , _KEY_INDICES
        );

        initializeEvdevStateAllAbs(
            _evdevState
            , _EVDEV
            , _ABS_INDICES
        );
    }

    void updateEvdevStateKey(
        tktemotejoy::EvdevState &               _evdevState
        , const tktemotejoy::EvdevKeyIndices &  _KEY_INDICES
        , const __u16 &                         _EVENT_CODE
        , const __s32 &                         _EVENT_VALUE
    )
    {
        const auto &    INDEX = _KEY_INDICES.at( _EVENT_CODE );
        if( INDEX < 0 ) {
            auto    oStringStream = std::ostringstream();

            oStringStream << "無効なキーコード : [" << _EVENT_CODE << ']';

            throw std::runtime_error( oStringStream.str() );
        }

        _evdevState.setButtonState(
            INDEX
            , _EVENT_VALUE
        );
    }

    void updateEvdevStateAbs(
        tktemotejoy::EvdevState &               _evdevState
        , const tktemotejoy::EvdevAbsIndices &  _ABS_INDICES
        , const __u16 &                         _EVENT_CODE
        , const __s32 &                         _EVENT_VALUE
    )
    {
        const auto &    INDEX = _ABS_INDICES.at( _EVENT_CODE );
        if( INDEX < 0 ) {
            auto    oStringStream = std::ostringstream();

            oStringStream << "無効な軸コード : [" << _EVENT_CODE << ']';

            throw std::runtime_error( oStringStream.str() );
        }

        _evdevState.setAxisState(
            INDEX
            , _EVENT_VALUE
        );
    }

    void updateEvdevState(
        tktemotejoy::EvdevState &               _evdevState
        , const int &                           _EVDEV
        , const tktemotejoy::EvdevKeyIndices &  _KEY_INDICES
        , const tktemotejoy::EvdevAbsIndices &  _ABS_INDICES
    )
    {
        auto        inputEvents = tktemotejoy::EvdevInputEvents();
        const auto  READ_EVENTS = tktemotejoy::readEvdevInputEvents(
            _EVDEV
            , inputEvents
        );

        const auto  INPUT_EVENTS_BEGIN = inputEvents.cbegin();
        const auto  INPUT_EVENTS_END = INPUT_EVENTS_BEGIN + READ_EVENTS;

        std::for_each(
            INPUT_EVENTS_BEGIN
            , INPUT_EVENTS_END
            , [
                &_KEY_INDICES
                , &_ABS_INDICES
                , &_evdevState
            ]
            (
                const input_event & _EVENT
            )
            {
                const auto &    EVENT_TYPE = _EVENT.type;
                const auto &    EVENT_CODE = _EVENT.code;
                const auto &    EVENT_VALUE = _EVENT.value;

                if( EVENT_TYPE == EV_KEY ) {
                    updateEvdevStateKey(
                        _evdevState
                        , _KEY_INDICES
                        , EVENT_CODE
                        , EVENT_VALUE
                    );
                } else if( EVENT_TYPE == EV_ABS ) {
                    updateEvdevStateAbs(
                        _evdevState
                        , _ABS_INDICES
                        , EVENT_CODE
                        , EVENT_VALUE
                    );
                }
            }
        );
    }

    void updatePspStateAndWriteToRepeaterWhenUpdated(
        tktemotejoy::PspState &             _pspState
        , tktusbrepeater::Writer &          _toRepeater
        , tktemotejoy::Mappings &           _mappings
        , const tktemotejoy::EvdevState &   _EVDEV_STATE
    )
    {
        auto    newPspState = tktemotejoy::PspState();
        _mappings.evdevStateToPspState(
            newPspState
            , _EVDEV_STATE
        );

        newPspState.runWhenDiff(
            _pspState
            , [
                &_toRepeater
                , &_pspState
                , &newPspState
            ]
            (
                const tktemotejoy::PspState::Bits & _BITS
            )
            {
                _toRepeater.write(
                    &_BITS
                    , sizeof( _BITS )
                );

                _pspState = newPspState;
            }
        );
    }

    void mainLoop(
        const int &                             _EVDEV
        , const tktemotejoy::EvdevKeyIndices &  _KEY_INDICES
        , const tktemotejoy::EvdevAbsIndices &  _ABS_INDICES
        , tktemotejoy::Mappings &               _mappings
        , tktusbrepeater::Writer &              _toRepeater
        , tktemotejoy::EvdevState &             _evdevState
        , tktemotejoy::PspState &               _pspState
    )
    {
        while( true ) {
            updateEvdevState(
                _evdevState
                , _EVDEV
                , _KEY_INDICES
                , _ABS_INDICES
            );

            updatePspStateAndWriteToRepeaterWhenUpdated(
                _pspState
                , _toRepeater
                , _mappings
                , _evdevState
            );
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

    int         evdev;
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

    auto    evdevState = tktemotejoy::EvdevState(
        BUTTONS
        , AXES
    );
    initializeEvdevState(
        evdevState
        , evdev
        , KEY_INDICES
        , ABS_INDICES
    );

    auto    pspState = tktemotejoy::PspState();

    try {
        mainLoop(
            evdev
            , KEY_INDICES
            , ABS_INDICES
            , mappings
            , toRepeater
            , evdevState
            , pspState
        );
    } catch( const std::runtime_error & _EX ) {
        writeClearBit( toRepeater );

        throw _EX;
    }

    return 0;
}
