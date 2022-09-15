#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/withrangeoneway.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace {
    class TestHandler final
    {
        bool &  called;

        const __s16         EXPECTED_FROM_MIN;
        const PspState &    EXPECTED_PSP_STATE;

    public:
        TestHandler(
            bool &              _called
            , const __s16       _EXPECTED_FROM_MIN
            , const PspState &  _EXPECTED_PSP_STATE
        )
            : called( _called )
            , EXPECTED_FROM_MIN( _EXPECTED_FROM_MIN )
            , EXPECTED_PSP_STATE( _EXPECTED_PSP_STATE )
        {
        }

        void operator()(
            const __s16     _FROM_MIN
            , PspState &    _pspState
        ) const
        {
            this->called = true;

            EXPECT_EQ( this->EXPECTED_FROM_MIN, _FROM_MIN );
            EXPECT_EQ( &( this->EXPECTED_PSP_STATE ), &_pspState );
        }
    };

    class WithRangeOneWayForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _VALUE
            , const __s16   _EXPECTED_FROM_MIN
            , const bool    _EXPECTED_CALLED
        ) const
        {
            auto    called = false;

            auto    pspState = PspState();

            auto    withRange = WithRangeOneWayForPspState(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , TestHandler(
                    called
                    , _EXPECTED_FROM_MIN
                    , pspState
                )
            );

            withRange(
                _VALUE
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED, called );
        }
    };
}

TEST_F(
    WithRangeOneWayForPspStateTest
    , Standard
)
{
    this->test(
        -100
        , 155
        , 10
        , 92
        , 192
        , true
    );
}

TEST_F(
    WithRangeOneWayForPspStateTest
    , DeadZone
)
{
    this->test(
        -100
        , 155
        , 10
        , -90
        , 0
        , false
    );
}
