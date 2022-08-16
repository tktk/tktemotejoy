#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    struct TestHandlerForPspState : public Mapping::HandlerForPspState
    {
        int &               calledCount;
        const __s16         EXPECTED_VALUE;
        const PspState &    PSP_STATE;

        TestHandlerForPspState(
            int &               _calledCount
            , const __s16       _EXPECTED_VALUE
            , const PspState &  _PSP_STATE
        )
            : Mapping::HandlerForPspState()
            , calledCount( _calledCount )
            , EXPECTED_VALUE( _EXPECTED_VALUE )
            , PSP_STATE( _PSP_STATE )
        {
        }

        void operator()(
            const __s16     _VALUE
            , PspState &    _pspState
        ) const
        {
            EXPECT_EQ( this->EXPECTED_VALUE, _VALUE );
            EXPECT_EQ( &( this->PSP_STATE ), &_pspState );

            const_cast< int & >( this->calledCount )++;
        }
    };

    class Mapping_operateAxisForPspStateTest : public ::testing::Test
    {
    public:
        void test(
            const int       _SET_HANDLER_KEY
            , const int     _OPERATE_AXIS_KEY
            , const __s16   _VALUE
            , const __s16   _EXPECTED_VALUE
            , const int     _EXPECTED_CALLED_COUNT
        )
        {
            auto    calledCount = 0;
            auto    pspState = PspState();

            auto    forPspStateUnique = Mapping::HandlerForPspStateUnique(
                new TestHandlerForPspState(
                    calledCount
                    , _EXPECTED_VALUE
                    , pspState
                )
            );

            auto    mapping = Mapping();

            mapping.setOperateAxisHandler(
                _SET_HANDLER_KEY
                , std::move( forPspStateUnique )
            );

            mapping.operateAxis(
                _OPERATE_AXIS_KEY
                , _VALUE
                , pspState
            );

            EXPECT_EQ( _EXPECTED_CALLED_COUNT, calledCount );
        }
    };
}

TEST_F(
    Mapping_operateAxisForPspStateTest
    , ExistsHandler
)
{
    this->test(
        10
        , 10
        , 20
        , 20
        , 1
    );
}

TEST_F(
    Mapping_operateAxisForPspStateTest
    , NotExistsHandler
)
{
    this->test(
        10
        , 20
        , 30
        , 0
        , 0
    );
}