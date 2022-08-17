#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <utility>

namespace {
    class TestHandler final : public Mapping::PressButtonHandlerForPspState
    {
        bool &  calledHandler;

    public:
        TestHandler(
            bool &  _calledHandler
        )
            : calledHandler( _calledHandler )
        {
        }

        void operator()(
            PspState &
        ) const override
        {
            this->calledHandler = true;
        }
    };

    class ToButtonHandlersTest : public ::testing::Test
    {
    public:
        void test(
            const __s16     _DEAD_ZONE
            , const __s16   _VALUE
            , const bool    _EXPECTED_CALLED_HANDLER1
            , const bool    _EXPECTED_CALLED_HANDLER2
        ) const
        {
            auto    calledHandler1 = false;
            auto    calledHandler2 = false;

            auto    handler1Unique = Mapping::PressButtonHandlerForPspStateUnique( new TestHandler( calledHandler1 ) );
            auto    handler2Unique = Mapping::PressButtonHandlerForPspStateUnique( new TestHandler( calledHandler2 ) );

            auto    toButtonHandlers = ToButtonHandlers(
                _DEAD_ZONE
                , ToButtonHandlersImpl(
                    std::move( handler1Unique )
                    , std::move( handler2Unique )
                )
            );

            auto    pspState = PspState();

            toButtonHandlers(
                _VALUE
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED_HANDLER1, calledHandler1 );
            EXPECT_EQ( _EXPECTED_CALLED_HANDLER2, calledHandler2 );
        }
    };
}

TEST_F(
    ToButtonHandlersTest
    , CallHandler1
)
{
    this->test(
        0
        , -1
        , true
        , false
    );
}

//TODO Minus

/*
TEST_F(
    ToAxisXTest
    , DeadZone
)
{
    this->test(
        1000
        , 2000
        , 500
        , 0x80800000
    );
}
*/
