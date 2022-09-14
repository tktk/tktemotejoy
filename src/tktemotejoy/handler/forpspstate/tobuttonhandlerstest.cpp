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

    class ToButtonHandlersForPspState_newTest : public ::testing::Test
    {
    public:
        void test(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _VALUE
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

            auto    toButtonHandlers = ToButtonHandlersForPspState_new(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToButtonHandlersForPspState_newImpl(
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

    class ToButtonHandlersForPspStateTest : public ::testing::Test
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

            auto    pspState = PspState();

            auto    handler1Unique = Mapping::PressButtonHandlerForPspStateUnique(
                new TestHandler(
                    calledHandler1
                    , pspState
                )
            );
            auto    handler2Unique = Mapping::PressButtonHandlerForPspStateUnique(
                new TestHandler(
                    calledHandler2
                    , pspState
                )
            );

            auto    toButtonHandlers = ToButtonHandlersForPspState(
                _DEAD_ZONE
                , ToButtonHandlersForPspStateImpl(
                    std::move( handler1Unique )
                    , std::move( handler2Unique )
                )
            );

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
    ToButtonHandlersForPspState_newTest
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

//TODO
/*
TEST_F(
    ToButtonHandlersForPspStateTest
    , CallHandlerPlus
)
{
    this->test(
        0
        , 1
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
        , 0
        , false
        , false
    );
}
*/

//REMOVEME
TEST_F(
    ToButtonHandlersForPspStateTest
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

//REMOVEME
TEST_F(
    ToButtonHandlersForPspStateTest
    , CallHandler2
)
{
    this->test(
        0
        , 1
        , false
        , true
    );
}

//REMOVEME
TEST_F(
    ToButtonHandlersForPspStateTest
    , DeadZone
)
{
    this->test(
        0
        , 0
        , false
        , false
    );
}
