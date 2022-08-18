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

    EXPECT_TRUE( calledWhenDiff );
    EXPECT_EQ( 0x80ff0000, bits );
}
