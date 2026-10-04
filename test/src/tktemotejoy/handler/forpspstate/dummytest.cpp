#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/dummy.h"
#include "tktemotejoy/pspstate.h"

TEST(
    DummyPressButtonHandlerForPspStateTest
    , OperatorCall
)
{
    auto    dummy = tktemotejoy::DummyPressButtonHandlerForPspState();

    auto    pspState = tktemotejoy::PspState();

    dummy( pspState );

    const auto  OTHER = tktemotejoy::PspState();

    auto    calledWhenDiff = false;

    pspState.diff(
        OTHER
        , [
            &calledWhenDiff
        ]
        (
            const tktemotejoy::PspState::Bits &
        )
        {
            calledWhenDiff = true;
        }
    );

    EXPECT_FALSE( calledWhenDiff );
}

TEST(
    DummyOperateAxisHandlerForPspStateTest
    , OperatorCall
)
{
    auto    dummy = tktemotejoy::DummyOperateAxisHandlerForPspState();

    auto    pspState = tktemotejoy::PspState();

    dummy(
        10
        , pspState
    );

    const auto  OTHER = tktemotejoy::PspState();

    auto    calledWhenDiff = false;

    pspState.diff(
        OTHER
        , [
            &calledWhenDiff
        ]
        (
            const tktemotejoy::PspState::Bits &
        )
        {
            calledWhenDiff = true;
        }
    );

    EXPECT_FALSE( calledWhenDiff );
}
