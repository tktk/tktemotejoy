#include "tktemotejoy/test.h"
#include "tktemotejoy/common.h"
#include <linux/joystick.h>

namespace {
    class JsEventAxisToPspStateAxisTest : public ::testing::Test
    {
    public:
        void test(
            const __s16             _JS_EVENT_AXIS
            , const PspState::Axis  _EXPECTED
        ) const
        {
            EXPECT_EQ( _EXPECTED, jsEventAxisToPspStateAxis( _JS_EVENT_AXIS ) );
        }
    };

    class JsEventAxisToPspStateAxisWithMaxTest : public ::testing::Test
    {
    public:
        void test(
            const __s16             _JS_EVENT_AXIS
            , const __s16           _MAX
            , const PspState::Axis  _EXPECTED
        ) const
        {
            EXPECT_EQ(
                _EXPECTED
                , jsEventAxisToPspStateAxis(
                    _JS_EVENT_AXIS
                    , _MAX
                )
            );
        }
    };
}

TEST_F(
    JsEventAxisToPspStateAxisTest
    , Max
)
{
    this->test(
        0x7fff
        , 0xff
    );
}

TEST_F(
    JsEventAxisToPspStateAxisTest
    , Zero
)
{
    this->test(
        0x0000
        , 0x80
    );
}

TEST_F(
    JsEventAxisToPspStateAxisTest
    , Min
)
{
    this->test(
        0x8000
        , 0x00
    );
}

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

//TODO GreaterThanMax
//TODO LesserThanMin
