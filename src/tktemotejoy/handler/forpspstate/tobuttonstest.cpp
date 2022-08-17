#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"

TEST(
    ToButtonsTest
    , OperatorCall
)
{
    auto    toButtons = ToButtons( 10 );

    auto    pspState = PspState();

    toButtons( pspState );

    auto    diffPspState = PspState();
    diffPspState.pressButtons( 20 );

    pspState.diff(
        diffPspState
        , [](
            const PspState::Bits &  _BITS
        )
        {
            EXPECT_EQ( _BITS, 0x0000000a );
        }
    );
}
