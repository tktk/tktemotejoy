#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
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

            ASSERT_EQ( this->EXPECTED_VALUE, _VALUE );
            ASSERT_EQ( &( this->EXPECTED_PSP_STATE ), &_pspState );
        }
    };

    class WithDeadZoneForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const __s16     _DEAD_ZONE
            , const __s16   _VALUE
            , const bool    _EXPECTED_CALLED
            , const __s16   _EXPECTED_VALUE
        ) const
        {
            auto    called = false;

            auto    pspState = PspState();

            auto    withDeadZone = WithDeadZoneForPspState(
                _DEAD_ZONE
                , TestHandler(
                    called
                    , _EXPECTED_VALUE
                    , pspState
                )
            );

            withDeadZone(
                _VALUE
                , pspState
            );

            ASSERT_EQ( _EXPECTED_CALLED, called );
        }
    };
}

TEST_F(
    WithDeadZoneForPspStateTest
    , OutOfDeadZoneForPspStatePlus
)
{
    this->test(
        0
        , 2000
        , true
        , 2000
    );
}

TEST_F(
    WithDeadZoneForPspStateTest
    , OutOfDeadZoneForPspStateMinus
)
{
    this->test(
        0
        , -2000
        , true
        , -2000
    );
}

TEST_F(
    WithDeadZoneForPspStateTest
    , DeadZoneForPspStatePlus
)
{
    this->test(
        1000
        , 1000
        , false
        , 0
    );
}

TEST_F(
    WithDeadZoneForPspStateTest
    , DeadZoneForPspStateMinus
)
{
    this->test(
        1000
        , -1000
        , false
        , 0
    );
}
