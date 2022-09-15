#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandler.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <utility>

namespace {
    class TestHandler final : public Mapping::PressButtonHandlerForPspState
    {
        bool &              calledHandler;
        const PspState &    EXPECTED_PSP_STATE;

    public:
        TestHandler(
            bool &              _calledHandler
            , const PspState &  _EXPECTED_PSP_STATE
        )
            : calledHandler( _calledHandler )
            , EXPECTED_PSP_STATE( _EXPECTED_PSP_STATE )
        {
        }

        void operator()(
            PspState &  _pspState
        ) const override
        {
            EXPECT_EQ( &( this->EXPECTED_PSP_STATE ), &_pspState );

            this->calledHandler = true;
        }
    };

    class ToButtonHandlerForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _VALUE
            , const bool    _EXPECTED_CALLED_HANDLER
        ) const
        {
            auto    calledHandler = false;

            auto    pspState = PspState();

            auto    handlerUnique = Mapping::PressButtonHandlerForPspStateUnique(
                new TestHandler(
                    calledHandler
                    , pspState
                )
            );

            auto    toButtonHandler = ToButtonHandlerForPspState(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToButtonHandlerForPspStateImpl( std::move( handlerUnique ) )
            );

            toButtonHandler(
                _VALUE
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED_HANDLER, calledHandler );
        }
    };
}

TEST_F(
    ToButtonHandlerForPspStateTest
    , CallHandler
)
{
    this->test(
        -100
        , 155
        , 10
        , 0
        , true
    );
}

TEST_F(
    ToButtonHandlerForPspStateTest
    , DeadZone
)
{
    this->test(
        -100
        , 155
        , 10
        , -90
        , false
    );
}
