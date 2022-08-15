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
        , 0x000010
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
        , 0x000040
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Left
)
{
    this->test(
        &PspState::pressLeft
        , true
        , 0x000080
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Right
)
{
    this->test(
        &PspState::pressRight
        , true
        , 0x000020
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Circle
)
{
    this->test(
        &PspState::pressCircle
        , true
        , 0x002000
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Cross
)
{
    this->test(
        &PspState::pressCross
        , true
        , 0x004000
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Triangle
)
{
    this->test(
        &PspState::pressTriangle
        , true
        , 0x001000
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Square
)
{
    this->test(
        &PspState::pressSquare
        , true
        , 0x008000
    );
}

TEST_F(
    PspState_diffButtonsTest
    , TriggerL
)
{
    this->test(
        &PspState::pressTriggerL
        , true
        , 0x000100
    );
}

TEST_F(
    PspState_diffButtonsTest
    , TriggerR
)
{
    this->test(
        &PspState::pressTriggerR
        , true
        , 0x000200
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Start
)
{
    this->test(
        &PspState::pressStart
        , true
        , 0x000008
    );
}

TEST_F(
    PspState_diffButtonsTest
    , Select
)
{
    this->test(
        &PspState::pressSelect
        , true
        , 0x000001
    );
}

//TODO AxisX
//TODO AxisY
