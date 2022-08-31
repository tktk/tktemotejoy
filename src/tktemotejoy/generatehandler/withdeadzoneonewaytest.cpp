#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/withdeadzoneoneway.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>
#include <memory>

namespace {
    struct TestHandler
    {
        const __u16     DEAD_ZONE;
        const long int  VALUE;
    };

    struct TestGenerateHandlerUnique : public GenerateHandlerWithDeadZoneOneWayUnique< TestGenerateHandlerUnique >
    {
        auto operatorCallImpl(
            const Json::object_t &  _OBJECT
            , const __u16           _DEAD_ZONE
        ) const
        {
            const auto &    VALUE = _OBJECT.at( "key" ).get_ref< const Json::number_integer_t & >();

            return std::unique_ptr< TestHandler >(
                new TestHandler{
                    _DEAD_ZONE
                    , VALUE
                }
            );
        }
    };

    class GenerateHandlerWithDeadZoneOneWayUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __u16       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            EXPECT_EQ( _EXPECTED_VALUE, handlerUnique->VALUE );
        }

        void testAnyThrow(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            EXPECT_ANY_THROW( TestGenerateHandlerUnique()( OBJECT ) );
        }
    };
}

TEST_F(
    GenerateHandlerWithDeadZoneOneWayUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "deadZone" : 10000,
    "key" : 20
})"
        , -22767
        , 20
    );
}

TEST_F(
    GenerateHandlerWithDeadZoneOneWayUniqueTest
    , NotExistsDeadZone
)
{
    this->test(
        R"({
    "key" : 20
})"
        , -32767
        , 20
    );
}

TEST_F(
    GenerateHandlerWithDeadZoneOneWayUniqueTest
    , FailedNotUnsignedDeadZone
)
{
    this->testAnyThrow(
        R"({
    "deadZone" : -10,
    "key" : 20
})"
    );
}