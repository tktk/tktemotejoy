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
        , 20
        , 10
    );
}

//TODO MaxGreaterThanMinOdd

TEST_F(
    CalcMinToCenterTest
    , MaxLesserThanMin
)
{
    this->test(
        -40
        , 0
        , 20
    );
}

//TODO MaxLesserThanMinOdd
