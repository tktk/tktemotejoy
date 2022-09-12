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

        ioctl(
            _DESCRIPTOR
            , EVIOCGNAME( name.size() )
            , name.data()
        );

        std::cout << "デバイス名 : " << '"' << name.data() << '"' << std::endl;
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
        const EvdevKeyIndices & _KEY_INDICES
    )
    {
        const auto  COUNT = countAvailableIndices( _KEY_INDICES );
        std::cout << "有効なキー数 : " << COUNT << std::endl;
    }

    void showAvailableAbssCount(
        const EvdevAbsIndices & _ABS_INDICES
    )
    {
        const auto  COUNT = countAvailableIndices( _ABS_INDICES );
        std::cout << "有効な軸数 : " << COUNT << std::endl;
    }

    template< typename INDICES_T >
    void showAvailableEventIndices(
        const INDICES_T &   _INDICES
    )
    {
        const auto  SIZE = _INDICES.size();
        for( auto i = typename INDICES_T::size_type( 0 ) ; i < SIZE ; i++ ) {
            const auto & INDEX = _INDICES.at( i );

            if( INDEX >= 0 ) {
                std::cout << INDEX << " : code(" << i << ')' << std::endl;
            }
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
    showAvailableEventIndices( KEY_INDICES );
    showAvailableAbssCount( ABS_INDICES );
    showAvailableEventIndices( ABS_INDICES );

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
