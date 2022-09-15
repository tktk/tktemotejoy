#include "tktemotejoy/commandlineoptions.h"
#include "tktemotejoy/file.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/joystickstate.h"
#include "tktemotejoy/tousbhostfs.h"
#include "tktemotejoy/joystick.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include <string>
#include <iostream>
#include <chrono>
#include <cstddef>
#include <linux/input.h>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <array>

namespace chrono = std::chrono;

namespace {
    auto generateButtons(
        const std::size_t & _BUTTONS
    )
    {
        return PspState::Buttons( 1 << ( _BUTTONS % 16 ) );
    }

    auto generateMappings(
        const std::size_t & _BUTTONS
    )
    {
        auto    mapping = Mapping(
            _BUTTONS
            , 0
        );

        for( auto i = std::size_t( 0 ) ; i < _BUTTONS ; i++ ) {
            mapping.setHandler(
                i
                , Mapping::handlerUnique( new ToButtons( generateButtons( i ) ) )
            );
        }

        auto    impl = Mappings::Impl();

        impl.emplace_back( std::move( mapping ) );

        return Mappings(
            std::move( impl )
            , 0
        );
    }
}

int main(
)
{
/*
    const auto  BUTTONS = KEY_MAX + ABS_MAX;
*/
    const auto  KEYS = std::vector< int >(
        {
            100,
            101,
            102,
            103,
            104,
            105,
            106,
            107,
            108,
            109,
            200,
            201,
            202,
            203,
            204,
            205,
            206,
            207,
            208,
            209,
            300,
            301,
            302,
            303,
            304,
            305,
            306,
            307,
            308,
            309,
            400,
            401,
            402,
            403,
            404,
            405,
            406,
            407,
            408,
            409,
        }
    );
    const auto  BUTTONS = KEYS.size();

    auto    codeToIndex = std::array<
        int
        , 500
    >();

    auto    index = 0;
    for( auto i = 0 ; i < codeToIndex.size() ; i++ ) {
        if( std::binary_search(
            KEYS.begin()
            , KEYS.end()
            , i
        ) == true ) {
            codeToIndex[ i ] = index;
            index++;
        } else {
            codeToIndex[ i ] = -1;
        }
    }

    auto    mappings = generateMappings( BUTTONS );

    auto    joystickState = JoystickState(
        BUTTONS
        , 0
    );

    std::cout << "joystickStateToPspState()開始" << std::endl;

    const auto  START_TIME = chrono::steady_clock::now();

    const auto  BEGIN = KEYS.cbegin();
    const auto  END = KEYS.cend();
    for( const auto & KEY : KEYS ) {
/*
        const auto  IT = std::lower_bound(
            BEGIN
            , END
            , KEY
        );
        if( IT == END ) {
            throw std::runtime_error( "そんなキーないゾ" );
        }

        joystickState.setButtonState(
            std::distance(
                BEGIN
                , IT
            )
            , 1
        );
*/
        const auto &    INDEX = codeToIndex[ KEY ];
        if( INDEX < 0 ) {
            throw std::runtime_error( "そんなキーないゾ" );
        }

        joystickState.setButtonState(
            INDEX
            , 1
        );
    }
/*
    for( auto i = 0 ; i < BUTTONS ; i++ ) {
        joystickState.setButtonState(
            i
            , 1
        );
    }
*/

    auto    pspState = PspState();

    mappings.joystickStateToPspState(
        pspState
        , joystickState
    );

    const auto  END_TIME = chrono::steady_clock::now();

    std::cout << "joystickStateToPspState()終了" << std::endl;

    const auto  DURATION = chrono::duration_cast< chrono::nanoseconds >( END_TIME - START_TIME );

    std::cout << "所要時間 : " << DURATION.count() << "ナノ秒" << std::endl;

    return 0;
}
