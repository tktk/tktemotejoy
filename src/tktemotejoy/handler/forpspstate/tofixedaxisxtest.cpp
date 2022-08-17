#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/pspstate.h"

TEST(
    ToFixedAxisXTest
    , OperatorCall
)
{
    auto    toFixedAxisX = ToFixedAxisX( 32767 );

    auto    pspState = PspState();

    toFixedAxisX( pspState );

    auto    diffPspState = PspState();
    diffPspState.pressButtons( 10 );

    pspState.diff(
        diffPspState
        , [](
            const PspState::Bits &  _BITS
        )
        {
            EXPECT_EQ( 0x80ff0000, _BITS );
        }
    );
}
