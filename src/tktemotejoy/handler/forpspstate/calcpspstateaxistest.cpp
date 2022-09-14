#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/calcpspstateaxis.h"
#include <linux/input.h>

namespace {
    class CalcPspStateAxisTest : public ::testing::Test
    {
    public:
        void test(
            const __s16             _VALUE
            , const __s16           _LIMIT
            , const PspState::Axis  _EXPECTED
        ) const
        {
            EXPECT_EQ(
                _EXPECTED
                , calcPspStateAxis(
                    _VALUE
                    , _LIMIT
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
        , 0xc0
    );
}

TEST_F(
    CalcPspStateAxisTest
    , OverLimit
)
{
    this->test(
        256
        , 256
        , 0xff
    );
}

//TODO OverLimitMinus

//TODO
/*
TEST_F(
    JsEventAxisToPspStateAxisWithMaxTest
    , LesserThanMin
)
{
    this->test(
        -20002
        , 20000
        , 0x00
    );
}
*/
