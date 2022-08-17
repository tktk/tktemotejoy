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
            EXPECT_EQ( 0x8080000a, _BITS );
        }
    );
}
