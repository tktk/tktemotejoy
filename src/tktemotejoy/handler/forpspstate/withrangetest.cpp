#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/withrange.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace {
    class TestHandler final
    {
        bool &  called;

        const __s32         EXPECTED_FROM_CENTER;
        const PspState &    EXPECTED_PSP_STATE;

    public:
        TestHandler(
            bool &              _called
            , const __s32       _EXPECTED_FROM_CENTER
            , const PspState &  _EXPECTED_PSP_STATE
        )
            : called( _called )
            , EXPECTED_FROM_CENTER( _EXPECTED_FROM_CENTER )
            , EXPECTED_PSP_STATE( _EXPECTED_PSP_STATE )
        {
        }

        void operator()(
            const __s32     _FROM_CENTER
            , PspState &    _pspState
        ) const
        {
            this->called = true;

            EXPECT_EQ( this->EXPECTED_FROM_CENTER, _FROM_CENTER );
            EXPECT_EQ( &( this->EXPECTED_PSP_STATE ), &_pspState );
        }
    };

    class WithRangeForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _VALUE
            , const __s32   _EXPECTED_FROM_CENTER
            , const bool    _EXPECTED_CALLED
        ) const
        {
            auto    called = false;

            auto    pspState = PspState();

            auto    withRange = WithRangeForPspState(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , TestHandler(
                    called
                    , _EXPECTED_FROM_CENTER
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
    WithRangeForPspStateTest
    , Standard
)
{
    this->test(
        0
        , 255
        , 10
        , 192
        , 64
        , true
    );
}

TEST_F(
    WithRangeForPspStateTest
    , DeadZone
)
{
    this->test(
        0
        , 255
        , 10
        , 138
        , 0
        , false
    );
}
