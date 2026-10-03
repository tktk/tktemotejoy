#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>
#include <cstddef>

namespace {
    class TestHandlerForPspState final : public Mapping::OperateAxisHandlerForPspState
    {
        int &               calledCount;
        const __s32         EXPECTED_VALUE;
        const PspState &    PSP_STATE;

    public:
        TestHandlerForPspState(
            int &               _calledCount
            , const __s32       _EXPECTED_VALUE
            , const PspState &  _PSP_STATE
        )
            : Mapping::OperateAxisHandlerForPspState()
            , calledCount( _calledCount )
            , EXPECTED_VALUE( _EXPECTED_VALUE )
            , PSP_STATE( _PSP_STATE )
        {
        }

        void operator()(
            const __s32     _VALUE
            , PspState &    _pspState
        ) const override
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
            const std::size_t   _SET_HANDLER_INDEX
            , const std::size_t _OPERATE_AXIS_INDEX
            , const __s32       _VALUE
            , const __s32       _EXPECTED_VALUE
            , const int         _EXPECTED_CALLED_COUNT
        ) const
        {
            auto    calledCount = 0;
            auto    pspState = PspState();

            auto    handlerUnique = Mapping::handlerUnique(
                new TestHandlerForPspState(
                    calledCount
                    , _EXPECTED_VALUE
                    , pspState
                )
            );

            auto    mapping = Mapping(
                0
                , _OPERATE_AXIS_INDEX + 1
            );

            mapping.setHandler(
                _SET_HANDLER_INDEX
                , std::move( handlerUnique )
            );

            mapping.operateAxis(
                _OPERATE_AXIS_INDEX
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
