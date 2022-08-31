#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/withdeadzoneoneway.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    class TestHandler final
    {
        bool &  called;

        const __u16         EXPECTED_VALUE;
        const PspState &    EXPECTED_PSP_STATE;

    public:
        TestHandler(
            bool &              _called
            , const __u16       _EXPECTED_VALUE
            , const PspState &  _EXPECTED_PSP_STATE
        )
            : called( _called )
            , EXPECTED_VALUE( _EXPECTED_VALUE )
            , EXPECTED_PSP_STATE( _EXPECTED_PSP_STATE )
        {
        }

        void operator()(
            const __u16     _VALUE
            , PspState &    _pspState
        ) const
        {
            this->called = true;

            EXPECT_EQ( this->EXPECTED_VALUE, _VALUE );
            EXPECT_EQ( &( this->EXPECTED_PSP_STATE ), &_pspState );
        }
    };

    class WithDeadZoneOneWayForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const __u16     _DEAD_ZONE
            , const __s16   _VALUE
            , const __u16   _EXPECTED_VALUE
            , const bool    _EXPECTED_CALLED
        ) const
        {
            auto    called = false;

            auto    pspState = PspState();

            auto    withDeadZoneOneWay = WithDeadZoneOneWayForPspState(
                _DEAD_ZONE
                , TestHandler(
                    called
                    , _EXPECTED_VALUE
                    , pspState
                )
            );

            withDeadZoneOneWay(
                _VALUE
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED, called );
        }
    };
}

TEST_F(
    WithDeadZoneOneWayForPspStateTest
    , OutOfDeadZone
)
{
    this->test(
        50000
        , 60000 ^ 0x8000
        , 60000
        , true
    );
}

TEST_F(
    WithDeadZoneOneWayForPspStateTest
    , DeadZone
)
{
    this->test(
        50000
        , 40000 ^ 0x8000
        , 0
        , false
    );
}
