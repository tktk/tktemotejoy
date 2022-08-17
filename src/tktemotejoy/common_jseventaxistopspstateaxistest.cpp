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

//TODO Zero
//TODO Min
