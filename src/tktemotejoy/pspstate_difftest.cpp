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
    , Buttons
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.pressButtons( 0x1234 );
        }
        , true
        , 0x00001234
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

TEST_F(
    PspState_diffTest
    , AxisX
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.operateAxisX( 10 );
        }
        , true
        , 0x000a0000
    );
}

TEST_F(
    PspState_diffTest
    , AxisY
)
{
    this->test(
        [](
            PspState &  _pspState
        )
        {
            _pspState.operateAxisY( 20 );
        }
        , true
        , 0x14000000
    );
}
