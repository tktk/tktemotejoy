#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisy.h"
#include "tktemotejoy/pspstate.h"

TEST(
    ToFixedAxisYTest
    , OperatorCall
)
{
    auto    toFixedAxisY = ToFixedAxisY( 32767 );

    auto    pspState = PspState();

    toFixedAxisY( pspState );

    auto    diffPspState = PspState();
    diffPspState.pressButtons( 10 );

    pspState.diff(
        diffPspState
        , [](
            const PspState::Bits &  _BITS
        )
        {
            EXPECT_EQ( 0xff000000, _BITS );
        }
    );
}
