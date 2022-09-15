#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>
#include <cstddef>

namespace {
    class TestHandlerForPspState final : public Mapping::PressButtonHandlerForPspState
    {
        int &               calledCount;
        const PspState &    PSP_STATE;

    public:
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
            const std::size_t   _SET_HANDLER_INDEX
            , const std::size_t _PRESS_BUTTON_INDEX
            , const int         _EXPECTED_CALLED_COUNT
        ) const
        {
            auto    calledCount = 0;
            auto    pspState = PspState();

            auto    handlerUnique = Mapping::handlerUnique(
                new TestHandlerForPspState(
                    calledCount
                    , pspState
                )
            );

            auto    mapping = Mapping(
                _PRESS_BUTTON_INDEX + 1
                , 0
            );

            mapping.setHandler(
                _SET_HANDLER_INDEX
                , std::move( handlerUnique )
            );

            mapping.pressButton(
                _PRESS_BUTTON_INDEX
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
