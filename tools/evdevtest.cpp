#include "tktemotejoy/evdev.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstddef>
#include <linux/input.h>
#include <sys/ioctl.h>

namespace {
    void showDeviceName(
        const int   _DESCRIPTOR
    )
    {
        auto    name = std::array<
            char
            , 256
        >();
        auto    namePtr = name.data();

        ioctl(
            _DESCRIPTOR
            , EVIOCGNAME( name.size() )
            , namePtr
        );

        std::cout << "デバイス名 : " << '"' << namePtr << '"' << std::endl;
    }

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

    void showAvailableKeysCount(
        const EvdevKeyIndices & _INDICES
    )
    {
        const auto  COUNT = countAvailableIndices( _INDICES );
        std::cout << "有効なキー数 : " << COUNT << std::endl;
    }

    void showAvailableAbssCount(
        const EvdevAbsIndices & _INDICES
    )
    {
        const auto  COUNT = countAvailableIndices( _INDICES );
        std::cout << "有効な軸数 : " << COUNT << std::endl;
    }

    void showAvailableKeys(
        const int                   _DESCRIPTOR
        , const EvdevKeyIndices &   _INDICES
    )
    {
        const auto  KEY_STATES = generateEvdevKeyStates( _DESCRIPTOR );

        const auto  SIZE = _INDICES.size();
        for( auto i = EvdevKeyIndices::size_type( 0 ) ; i < SIZE ; i++ ) {
            const auto & INDEX = _INDICES.at( i );

            if( INDEX >= 0 ) {
                const auto  VALUE = KEY_STATES.test( i ) == true ? 1 : 0;

                std::cout << INDEX
                    << " : code(" << i
                    << "), value(" << VALUE
                    << ')' << std::endl;
            }
        }
    }

    void showAvailableAbss(
        const int                   _DESCRIPTOR
        , const EvdevAbsIndices &   _INDICES
    )
    {
        const auto  ABS_DATA_ARRAY = generateEvdevAbsDataArray( _DESCRIPTOR );

        const auto  SIZE = _INDICES.size();
        for( auto i = EvdevKeyIndices::size_type( 0 ) ; i < SIZE ; i++ ) {
            const auto & INDEX = _INDICES.at( i );

            if( INDEX < 0 ) {
                continue;
            }

            const auto &    ABS_DATA = ABS_DATA_ARRAY.at( i );

            std::cout << INDEX
                << " : code(" << i
                << "), value(" << ABS_DATA.value
                << "), min(" << ABS_DATA.min
                << "), max(" << ABS_DATA.max
                << "), fuzz(" << ABS_DATA.fuzz
                << "), flat(" << ABS_DATA.flat
                << "), resolution(" << ABS_DATA.resolution
                << ')' << std::endl;
        }
    }
}

int main(
    const int               _ARGC
    , const char * const *  _ARGV
)
{
    if( _ARGC <= 1 ) {
        std::cerr << "使い方 : " << _ARGV[ 0 ] << " デバイスファイル" << std::endl;

        return 1;
    }

    const auto  DEVICE_FILE_PATH = std::string( _ARGV[ 1 ] );

    int evdev;
    const auto  EVDEV_CLOSER = openEvdev(
        evdev
        , DEVICE_FILE_PATH
    );

    showDeviceName( evdev );

    const auto  KEY_INDICES = generateEvdevKeyIndices( evdev );
    const auto  ABS_INDICES = generateEvdevAbsIndices( evdev );

    showAvailableKeysCount( KEY_INDICES );
    showAvailableKeys(
        evdev
        , KEY_INDICES
    );
    showAvailableAbssCount( ABS_INDICES );
    showAvailableAbss(
        evdev
        , ABS_INDICES
    );

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

                    std::cout << "キーイベント : index(" << INDEX << "), value(" << EVENT_VALUE << ')' << std::endl;
                } else if( EVENT_TYPE == EV_ABS ) {
                    const auto &    INDEX = ABS_INDICES.at( EVENT_CODE );

                    std::cout << "軸イベント : index(" << INDEX << "), value(" << EVENT_VALUE << ')' << std::endl;
                }
            }
        );
    }

    return 0;
}
