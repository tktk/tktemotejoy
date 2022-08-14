#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    struct TestHandlerForPspState : public Mapping::HandlerForPspState
    {
        int &               calledCount;
        const PspState &    PSP_STATE;

        TestHandlerForPspState(
            int &               _calledCount
            , const PspState &  _PSP_STATE
        )
            : Mapping::HandlerForPspState()
            , calledCount( _calledCount )
            , PSP_STATE( _PSP_STATE )
        {
        }

        void operator()(
            const __s16
            , PspState &    _pspState
        ) const
        {
            ASSERT_EQ( &( this->PSP_STATE ), &_pspState );

            const_cast< int & >( this->calledCount )++;
        }
    };

    class Mapping_pressButtonForPspStateTest : public ::testing::Test
    {
    public:
        void test(
        )
        {
            auto    calledCount = 0;
            auto    pspState = PspState();

            auto    forPspStateUnique = Mapping::HandlerForPspStateUnique(
                new TestHandlerForPspState(
                    calledCount
                    , pspState
                )
            );

            auto    mapping = Mapping();

            mapping.setPressButtonHandler(
                10
                , std::move( forPspStateUnique )
            );

            mapping.pressButton(
                10
                , pspState
            );

            ASSERT_EQ( 1, calledCount );
        }
    };
}

TEST_F(
    Mapping_pressButtonForPspStateTest
    , ExistsProc
)
{
    this->test();
}
