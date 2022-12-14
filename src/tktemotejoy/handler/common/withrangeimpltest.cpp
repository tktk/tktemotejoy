#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/common/withrangeimpl.h"
#include <linux/input.h>

namespace {
    class TestHandler final
    {
        bool &  called;

        const __s32 EXPECTED_FROM_CENTER;

    public:
        TestHandler(
            bool &          _called
            , const __s32   _EXPECTED_FROM_CENTER
        )
            : called( _called )
            , EXPECTED_FROM_CENTER( _EXPECTED_FROM_CENTER )
        {
        }

        auto operator()(
            const __s32     _FROM_CENTER
        ) const
        {
            this->called = true;

            EXPECT_EQ( this->EXPECTED_FROM_CENTER, _FROM_CENTER );

            return _FROM_CENTER;
        }
    };

    class WithRangeImplTest : public ::testing::Test
    {
    public:
        void test(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _DEFAULT_VALUE
            , const __s32   _VALUE
            , const __s32   _EXPECTED
            , const __s32   _EXPECTED_FROM_CENTER
            , const bool    _EXPECTED_CALLED
        ) const
        {
            auto    called = false;

            auto    withRange = WithRangeImpl(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , TestHandler(
                    called
                    , _EXPECTED_FROM_CENTER
                )
            );

            EXPECT_EQ(
                _EXPECTED
                , withRange(
                    [
                        &_DEFAULT_VALUE
                    ]
                    {
                        return _DEFAULT_VALUE;
                    }
                    , _VALUE
                )
            );

            EXPECT_EQ( _EXPECTED_CALLED, called );
        }
    };
}

TEST_F(
    WithRangeImplTest
    , MaxGreaterThanMin
)
{
    this->test(
        0
        , 255
        , 10
        , 20
        , 192
        , 64
        , 64
        , true
    );
}

TEST_F(
    WithRangeImplTest
    , MaxLesserThanMin
)
{
    this->test(
        255
        , 0
        , 10
        , 20
        , 192
        , -65
        , -65
        , true
    );
}

TEST_F(
    WithRangeImplTest
    , DeadZonePlus
)
{
    this->test(
        0
        , 255
        , 10
        , 20
        , 138
        , 20
        , 0
        , false
    );
}

TEST_F(
    WithRangeImplTest
    , DeadZoneMinus
)
{
    this->test(
        0
        , 255
        , 10
        , 20
        , 118
        , 20
        , 0
        , false
    );
}
