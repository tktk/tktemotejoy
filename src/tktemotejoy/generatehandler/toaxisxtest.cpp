#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>

namespace {
    struct TestToAxisX
    {
        const void * DUMMY;
        const __s16 DEAD_ZONE;
        const __s16 MAX;
    };

    class GenerateToAxisXTest : public ::testing::Test
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

            auto    handlerUnique = generateToAxisXUnique( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            const auto &    TEST_TO_AXIS_X = reinterpret_cast< const TestToAxisX & >( *handlerUnique );

            EXPECT_EQ( _EXPECTED_DEAD_ZONE, TEST_TO_AXIS_X.DEAD_ZONE );
            EXPECT_EQ( _EXPECTED_MAX, TEST_TO_AXIS_X.MAX );
        }
    };
}

//TODO ToAxisXが生成されているかテストできていない
TEST_F(
    GenerateToAxisXTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisX",
    "deadZone" : 10,
    "max" : 20
})"
        , 10
        , 20
    );
}
