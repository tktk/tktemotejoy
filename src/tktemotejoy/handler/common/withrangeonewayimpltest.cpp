#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/common/withrangeonewayimpl.h"
#include <linux/input.h>

namespace {
    class TestHandler final
    {
        bool &  called;

        const __s16 EXPECTED_FROM_MIN;

    public:
        TestHandler(
            bool &          _called
            , const __s16   _EXPECTED_FROM_MIN
        )
            : called( _called )
            , EXPECTED_FROM_MIN( _EXPECTED_FROM_MIN )
        {
        }

        auto operator()(
            const __s16     _FROM_MIN
        ) const
        {
            this->called = true;

            EXPECT_EQ( this->EXPECTED_FROM_MIN, _FROM_MIN );

            return _FROM_MIN;
        }
    };

    class WithRangeOneWayImplTest : public ::testing::Test
    {
    public:
        void test(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _DEFAULT_VALUE
            , const __s16   _VALUE
            , const __s16   _EXPECTED
            , const __s16   _EXPECTED_FROM_MIN
            , const bool    _EXPECTED_CALLED
        ) const
        {
            auto    called = false;

            auto    withRange = WithRangeOneWayImpl(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , TestHandler(
                    called
                    , _EXPECTED_FROM_MIN
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
    WithRangeOneWayImplTest
    , MaxGreaterThanMin
)
{
    this->test(
        -100
        , 155
        , 10
        , 20
        , 92
        , 192
        , 192
        , true
    );
}

TEST_F(
    WithRangeOneWayImplTest
    , MaxLesserThanMin
)
{
    this->test(
        155
        , -100
        , 10
        , 20
        , 92
        , 63
        , 63
        , true
    );
}

TEST_F(
    WithRangeOneWayImplTest
    , DeadZone
)
{
    this->test(
        -100
        , 155
        , 10
        , 20
        , -90
        , 20
        , 0
        , false
    );
}
