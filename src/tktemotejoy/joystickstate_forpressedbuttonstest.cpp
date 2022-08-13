#include "tktemotejoy/test.h"
#include "tktemotejoy/joystickstate.h"
#include <vector>
#include <set>

namespace {
    using Indices = std::set< JoystickState::States::size_type >;

    class JoystickState_forPressedButtonsTest : public ::testing::Test
    {
    public:
        void test(
            JoystickState                               _joystickState
            , const Indices                             _PRESS_BUTTON_INDICES
            , const bool                                _RETURNS_FOR_PROC
            , const bool                                _EXPECTED
            , const JoystickState::States::size_type    _EXPECTED_CALL_COUNT
            , const bool                                _TEST_CALLED_INDICES
        )
        {
            for( const auto & INDEX : _PRESS_BUTTON_INDICES ) {
                _joystickState.setButtonState(
                    INDEX
                    , 1
                );
            }

            auto    callCount = 0;
            auto    calledIndices = Indices();
            EXPECT_EQ(
                _EXPECTED
                , _joystickState.forPressedButtons(
                    [
                        &_RETURNS_FOR_PROC
                        , &callCount
                        , &calledIndices
                    ]
                    (
                        const JoystickState::States::size_type      _INDEX
                        , const JoystickState::States::value_type
                    ) -> bool
                    {
                        callCount++;
                        calledIndices.insert( _INDEX );

                        return _RETURNS_FOR_PROC;
                    }
                )
            );

            EXPECT_EQ( _EXPECTED_CALL_COUNT, callCount );
            if( _TEST_CALLED_INDICES == true ) {
                EXPECT_EQ( _PRESS_BUTTON_INDICES, calledIndices );
            }
        }
    };
}

TEST_F(
    JoystickState_forPressedButtonsTest
    , ForAllPressedButtons
)
{
    this->test(
        JoystickState(
            5
            , 5
        )
        , Indices{
            1
            , 2
            , 3
        }
        , false
        , false
        , 3
        , true
    );
}

TEST_F(
    JoystickState_forPressedButtonsTest
    , Breaked
)
{
    this->test(
        JoystickState(
            5
            , 5
        )
        , Indices{
            1
            , 2
            , 3
        }
        , true
        , true
        , 1
        , false
    );
}
