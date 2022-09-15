#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/common/calcmintocenter.h"
#include <linux/input.h>

namespace {
    class CalcMinToCenterTest : public ::testing::Test
    {
    public:
        void test(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _EXPECTED
        ) const
        {
            EXPECT_EQ(
                _EXPECTED
                , calcMinToCenter(
                    _MIN
                    , _MAX
                )
            );
        }
    };
}

TEST_F(
    CalcMinToCenterTest
    , MaxGreaterThanMin
)
{
    this->test(
        0
        , 256
        , 128
    );
}

TEST_F(
    CalcMinToCenterTest
    , MaxGreaterThanMinOdd
)
{
    this->test(
        0
        , 255
        , 128
    );
}

TEST_F(
    CalcMinToCenterTest
    , MaxLesserThanMin
)
{
    this->test(
        512
        , 0
        , 256
    );
}

TEST_F(
    CalcMinToCenterTest
    , MaxLesserThanMinOdd
)
{
    this->test(
        511
        , 0
        , 256
    );
}
