#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/dummy.h"

TEST(
    DummyPressButtonHandlerForPspStateTest
    , OperatorCall
)
{
    auto    dummy = DummyPressButtonHandlerForPspState();

    auto    pspState = PspState();

    dummy( pspState );

    const auto  OTHER = PspState();

    auto    calledWhenDiff = false;

    pspState.diff(
        OTHER
        , [
            &calledWhenDiff
        ]
        (
            const PspState::Bits &
        )
        {
            calledWhenDiff = true;
        }
    );

    EXPECT_FALSE( calledWhenDiff );
}
