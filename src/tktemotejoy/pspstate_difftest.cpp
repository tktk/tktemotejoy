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

TEST_F(
    PspState_diffTest
    , Down
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressDown();
        }
        , true
        , 0x000040
    );
}

TEST_F(
    PspState_diffTest
    , Left
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressLeft();
        }
        , true
        , 0x000080
    );
}

TEST_F(
    PspState_diffTest
    , Right
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressRight();
        }
        , true
        , 0x000020
    );
}

TEST_F(
    PspState_diffTest
    , Circle
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressCircle();
        }
        , true
        , 0x002000
    );
}

TEST_F(
    PspState_diffTest
    , Cross
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressCross();
        }
        , true
        , 0x004000
    );
}

TEST_F(
    PspState_diffTest
    , Triangle
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressTriangle();
        }
        , true
        , 0x001000
    );
}

TEST_F(
    PspState_diffTest
    , Square
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressSquare();
        }
        , true
        , 0x008000
    );
}

TEST_F(
    PspState_diffTest
    , TriggerL
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressTriggerL();
        }
        , true
        , 0x000100
    );
}

TEST_F(
    PspState_diffTest
    , TriggerR
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressTriggerR();
        }
        , true
        , 0x000200
    );
}

TEST_F(
    PspState_diffTest
    , Start
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressStart();
        }
        , true
        , 0x000008
    );
}

TEST_F(
    PspState_diffTest
    , Select
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressSelect();
        }
        , true
        , 0x000001
    );
}

TEST_F(
    PspState_diffTest
    , Same
)
{
    this->test(
        [](
            PspState &
        )
        {
        }
        , false
        , 0
    );
}

//TODO AxisX
//TODO AxisY
