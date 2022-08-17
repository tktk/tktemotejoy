#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/withdeadzone.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    class TestHandler
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

    class WithDeadZoneTest : public ::testing::Test
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

            auto    withDeadZone = WithDeadZone< TestHandler >(
                _DEAD_ZONE
                , called
                , _EXPECTED_VALUE
                , pspState
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
    WithDeadZoneTest
    , OutOfDeadZone
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
    WithDeadZoneTest
    , DeadZonePlus
)
{
    this->test(
        1000
        , 999
        , false
        , 0
    );
}

//TODO DeadZoneMinus
