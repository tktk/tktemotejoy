#include "tktemotejoy/test.h"
#include "tktemotejoy/pspstate.h"
#include <functional>

namespace {
    class PspState_diffTest : public ::testing::Test
    {
    public:
        void test(
            const std::function< void ( PspState & ) > &    _FOR_PSP_STATE
            , const bool                                    _EXPECTED_CALLED_WHEN_DIFF
            , const PspState::Bits                          _EXPECTED_BITS
        )
        {
            auto    pspState = PspState();

            _FOR_PSP_STATE( pspState );

            const auto  OTHER = PspState();

            auto    calledWhenDiff = false;
            auto    bits = PspState::Bits();

            pspState.diff(
                OTHER
                , [
                    &calledWhenDiff
                    , &bits
                ]
                (
                    const PspState::Bits &  _BITS
                )
                {
                    calledWhenDiff = true;
                    bits = _BITS;
                }
            );

            ASSERT_EQ( _EXPECTED_CALLED_WHEN_DIFF, calledWhenDiff );
            ASSERT_EQ( _EXPECTED_BITS, bits );
        }
    };
}

TEST_F(
    PspState_diffTest
    , Up
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressUp();
        }
        , true
        , 0x000010
    );
}

//TODO
/*
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

TEST_F(
    PspState_diffButtonsTest
    , Same
)
{
    this->test(
        nullptr
        , false
        , 0
    );
}

//TODO AxisX
//TODO AxisY
*/
