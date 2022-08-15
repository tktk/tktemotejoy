#include "tktemotejoy/test.h"
#include "tktemotejoy/pspstate.h"

namespace {
    class PspState_diffButtonsTest : public ::testing::Test
    {
    public:
        void test(
            void ( PspState:: *             _PRESS_BUTTON )()
            , const bool                    _EXPECTED_CALLED_WHEN_DIFF_BUTTONS
            , const PspState::ButtonBits    _EXPECTED_BUTTON_BITS
        )
        {
            auto    pspState = PspState();

            ( pspState.*_PRESS_BUTTON )();

            const auto  OTHER = PspState();

            auto    calledWhenDiffButtons = false;
            auto    buttonBits = PspState::ButtonBits();

            pspState.diff(
                OTHER
                , [
                    &calledWhenDiffButtons
                    , &buttonBits
                ]
                (
                    const PspState::ButtonBits &    _BUTTON_BITS
                )
                {
                    calledWhenDiffButtons = true;
                    buttonBits = _BUTTON_BITS;
                }
                , [](
                    const PspState::Axis &
                )
                {
                    ASSERT_FALSE( true );
                }
                , [](
                    const PspState::Axis &
                )
                {
                    ASSERT_FALSE( true );
                }
            );

            ASSERT_EQ( _EXPECTED_CALLED_WHEN_DIFF_BUTTONS, calledWhenDiffButtons );
            ASSERT_EQ( _EXPECTED_BUTTON_BITS, buttonBits );
        }
    };
}

TEST_F(
    PspState_diffButtonsTest
    , Up
)
{
    this->test(
        &PspState::pressUp
        , true
        , 0b10000
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Down
)
{
    this->test(
        &PspState::pressDown
        , true
        , 0b1000000
    );
}

//TODO Down
//TODO Left
//TODO Right
//TODO Circle
//TODO Cross
//TODO Triangle
//TODO Square
//TODO TriggerL
//TODO TriggerR
//TODO Start
//TODO Select
//TODO AxisX
//TODO AxisY
