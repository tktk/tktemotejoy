#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/withdeadzoneunsigned.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    class TestHandler final
    {
        bool &  called;

        const __s16         EXPECTED_VALUE;
        const PspState &    EXPECTED_PSP_STATE;

    public:
        TestHandler(
            bool &              _called
            , const __s16       _EXPECTED_VALUE
            , const PspState &  _EXPECTED_PSP_STATE
        )
            : called( _called )
            , EXPECTED_VALUE( _EXPECTED_VALUE )
            , EXPECTED_PSP_STATE( _EXPECTED_PSP_STATE )
        {
        }

        void operator()(
            const __s16     _VALUE
            , PspState &    _pspState
        ) const
        {
            this->called = true;

            EXPECT_EQ( this->EXPECTED_VALUE, _VALUE );
            EXPECT_EQ( &( this->EXPECTED_PSP_STATE ), &_pspState );
        }
    };

    class WithDeadZoneUnsignedForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const __u16     _DEAD_ZONE
            , const __s16   _VALUE
            , const __s16   _EXPECTED_VALUE
            , const bool    _EXPECTED_CALLED
        ) const
        {
            auto    called = false;

            auto    pspState = PspState();

            auto    withDeadZoneUnsigned = WithDeadZoneUnsignedForPspState(
                _DEAD_ZONE
                , TestHandler(
                    called
                    , _EXPECTED_VALUE
                    , pspState
                )
            );

            withDeadZoneUnsigned(
                _VALUE
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED, called );
        }
    };
}

TEST_F(
    WithDeadZoneUnsignedForPspStateTest
    , OutOfDeadZone
)
{
    this->test(
        50000
        , 60000
        , 60000
        , true
    );
}

TEST_F(
    WithDeadZoneUnsignedForPspStateTest
    , DeadZone
)
{
    this->test(
        50000
        , 40000
        , 0
        , false
    );
}
