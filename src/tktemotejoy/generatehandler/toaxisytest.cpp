#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>

namespace {
    struct TestToAxisY
    {
        const void * DUMMY;
        const __s16 DEAD_ZONE;
        const __s16 MAX;
    };

    class GenerateToAxisYTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_DEAD_ZONE
            , const __s16       _EXPECTED_MAX
        )
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = generateToAxisYUnique( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            const auto &    TEST_TO_AXIS_Y = reinterpret_cast< const TestToAxisY & >( *handlerUnique );

            EXPECT_EQ( _EXPECTED_DEAD_ZONE, TEST_TO_AXIS_Y.DEAD_ZONE );
            EXPECT_EQ( _EXPECTED_MAX, TEST_TO_AXIS_Y.MAX );
        }
    };
}

//TODO ToAxisYが生成できているかテストできていない
TEST_F(
    GenerateToAxisYTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisY",
    "deadZone" : 10,
    "max" : 20
})"
        , 10
        , 20
    );
}
