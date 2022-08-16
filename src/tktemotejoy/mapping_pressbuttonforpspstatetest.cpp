#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    struct TestHandlerForPspState final : public Mapping::PressButtonHandlerForPspState
    {
        int &               calledCount;
        const PspState &    PSP_STATE;

        TestHandlerForPspState(
            int &               _calledCount
            , const PspState &  _PSP_STATE
        )
            : Mapping::PressButtonHandlerForPspState()
            , calledCount( _calledCount )
            , PSP_STATE( _PSP_STATE )
        {
        }

        void operator()(
            PspState &  _pspState
        ) const override
        {
            EXPECT_EQ( &( this->PSP_STATE ), &_pspState );

            const_cast< int & >( this->calledCount )++;
        }
    };

    class Mapping_pressButtonForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const int   _SET_HANDLER_KEY
            , const int _PRESS_BUTTON_KEY
            , const int _EXPECTED_CALLED_COUNT
        )
        {
            auto    calledCount = 0;
            auto    pspState = PspState();

            auto    handlerUnique = Mapping::HandlerUnique(
                new TestHandlerForPspState(
                    calledCount
                    , pspState
                )
            );

            auto    mapping = Mapping();

            mapping.setHandler(
                _SET_HANDLER_KEY
                , std::move( handlerUnique )
            );

            mapping.pressButton(
                _PRESS_BUTTON_KEY
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED_COUNT, calledCount );
        }
    };
}

TEST_F(
    Mapping_pressButtonForPspStateTest
    , ExistsHandler
)
{
    this->test(
        10
        , 10
        , 1
    );
}

TEST_F(
    Mapping_pressButtonForPspStateTest
    , NotExistsHandler
)
{
    this->test(
        10
        , 20
        , 0
    );
}
