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

//TODO
/*
TEST_F(
    JsEventAxisToPspStateAxisWithMaxTest
    , Max
)
{
    this->test(
        20000
        , 20000
        , 0xff
    );
}

TEST_F(
    JsEventAxisToPspStateAxisWithMaxTest
    , Zero
)
{
    this->test(
        0
        , 20000
        , 0x80
    );
}

TEST_F(
    JsEventAxisToPspStateAxisWithMaxTest
    , Min
)
{
    this->test(
        -20000
        , 20000
        , 0x00
    );
}

TEST_F(
    JsEventAxisToPspStateAxisWithMaxTest
    , Half
)
{
    this->test(
        10000
        , 20000
        , 0xbf
    );
}

TEST_F(
    JsEventAxisToPspStateAxisWithMaxTest
    , GreaterThanMax
)
{
    this->test(
        20001
        , 20000
        , 0xff
    );
}

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
