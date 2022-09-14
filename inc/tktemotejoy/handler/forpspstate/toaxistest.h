#ifndef TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISTEST_H
#define TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISTEST_H

#include "tktemotejoy/test.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

template< typename GENERATE_TO_AXIS_T >
class ToAxisTest : public ::testing::Test
{
public:
    void test(
        const __s16             _MIN
        , const __s16           _MAX
        , const __s16           _DEAD_ZONE
        , const __s16           _LIMIT
        , const __s16           _VALUE
        , const bool            _EXPECTED_CALLED_WHEN_DIFF
        , const PspState::Bits  _EXPECTED_BITS
    ) const
    {
        auto    toAxis = GENERATE_TO_AXIS_T()(
            _MIN
            , _MAX
            , _DEAD_ZONE
            , _LIMIT
        );

        auto    pspState = PspState();

        toAxis(
            _VALUE
            , pspState
        );

        const auto  OTHER = PspState();

        auto    calledWhenDiff = false;

        pspState.diff(
            OTHER
            , [
                &_EXPECTED_BITS
                , &calledWhenDiff
            ]
            (
                const PspState::Bits &  _BITS
            )
            {
                calledWhenDiff = true;

                EXPECT_EQ( _EXPECTED_BITS, _BITS );
            }
        );

        EXPECT_EQ( _EXPECTED_CALLED_WHEN_DIFF, calledWhenDiff );
    }
};

#endif  // TKTEMOTEJOY_HANDLER_FORPSPSTATE_TOAXISTEST_H
