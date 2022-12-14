#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
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

    class ToButtonHandlersForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _VALUE
            , const bool    _EXPECTED_CALLED_HANDLER_MINUS
            , const bool    _EXPECTED_CALLED_HANDLER_PLUS
        ) const
        {
            auto    calledHandlerMinus = false;
            auto    calledHandlerPlus = false;

            auto    pspState = PspState();

            auto    handlerMinusUnique = Mapping::PressButtonHandlerForPspStateUnique(
                new TestHandler(
                    calledHandlerMinus
                    , pspState
                )
            );
            auto    handlerPlusUnique = Mapping::PressButtonHandlerForPspStateUnique(
                new TestHandler(
                    calledHandlerPlus
                    , pspState
                )
            );

            auto    toButtonHandlers = ToButtonHandlersForPspState(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToButtonHandlersForPspStateImpl(
                    std::move( handlerMinusUnique )
                    , std::move( handlerPlusUnique )
                )
            );

            toButtonHandlers(
                _VALUE
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED_HANDLER_MINUS, calledHandlerMinus );
            EXPECT_EQ( _EXPECTED_CALLED_HANDLER_PLUS, calledHandlerPlus );
        }
    };
}

TEST_F(
    ToButtonHandlersForPspStateTest
    , CallHandlerMinus
)
{
    this->test(
        0
        , 255
        , 10
        , 117
        , true
        , false
    );
}

TEST_F(
    ToButtonHandlersForPspStateTest
    , CallHandlerPlus
)
{
    this->test(
        0
        , 255
        , 10
        , 139
        , false
        , true
    );
}

TEST_F(
    ToButtonHandlersForPspStateTest
    , DeadZone
)
{
    this->test(
        0
        , 255
        , 10
        , 138
        , false
        , false
    );
}
