#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include <linux/input.h>

namespace {
    class CalcPspStateAxisTest : public ::testing::Test
    {
    public:
        void test(
            const __s32             _VALUE
            , const __s32           _LIMIT
            , const __s32           _ERASE_DEAD_ZONE
            , const PspState::Axis  _EXPECTED
        ) const
        {
            EXPECT_EQ(
                _EXPECTED
                , calcPspStateAxis(
                    _VALUE
                    , _LIMIT
                    , _ERASE_DEAD_ZONE
                )
            );
        }
    };
}

TEST_F(
    CalcPspStateAxisTest
    , Standard
)
{
    this->test(
        128
        , 256
        , 0
        , 0xc0
    );
}

TEST_F(
    CalcPspStateAxisTest
    , OverLimit_plus
)
{
    this->test(
        256
        , 256
        , 0
        , 0xff
    );
}

TEST_F(
    CalcPspStateAxisTest
    , OverLimit_minus
)
{
    this->test(
        -258
        , 256
        , 0
        , 0x00
    );
}

TEST_F(
    CalcPspStateAxisTest
    , EraseDeadZone_plus
)
{
    this->test(
        128
        , 256
        , 64
        , 0xe0
    );
}

//TODO EraseDeadZone_minus
