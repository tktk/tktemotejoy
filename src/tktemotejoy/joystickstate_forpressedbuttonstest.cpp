#include "fg/util/test.h"
#include "tktemotejoy/joystickstate.h"
#include <vector>
#include <set>

TEST(
    JoystickState_forPressedButtonsTest
    , MapAllPressedButtons
)
{
    using Indices = std::set< JoystickState::States::size_type >;

    const auto  PRESS_BUTTON_INDICES = Indices{
        2
        , 3
        , 4
    };

    auto    joystickState = JoystickState(
        5
        , 5
    );

    for( const auto & I : PRESS_BUTTON_INDICES ) {
        joystickState.setButtonState(
            I
            , 1
        );
    }

    auto    callCount = 0;
    auto    calledIndices = Indices();
    joystickState.forPressedButtons (
        [
            &callCount
            , &calledIndices
        ]
        (
            const JoystickState::States::size_type      _INDEX
            , const JoystickState::States::value_type
        ) -> bool
        {
            callCount++;
            calledIndices.insert( _INDEX );

            return false;
        }
    );

    EXPECT_EQ( PRESS_BUTTON_INDICES.size(), callCount );
    EXPECT_EQ( PRESS_BUTTON_INDICES, calledIndices );
}

//TODO Breaked
