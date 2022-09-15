#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/common/calcrangedirection.h"
#include <linux/input.h>

namespace {
    class CalcRangeDirectionTest : public ::testing::Test
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
                , calcRangeDirection(
                    _MIN
                    , _MAX
                )
            );
        }
    };
}

TEST_F(
    CalcRangeDirectionTest
    , MaxGreaterThanMin
)
{
    this->test(
        0
        , 255
        , 1
    );
}

//TODO MaxLesserThanMin
//TODO MaxEqualsMin
