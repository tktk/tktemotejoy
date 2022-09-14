#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/withrange.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <string>
#include <memory>

namespace {
    struct TestHandler
    {
        const __s16     MIN;
        const __s16     MAX;
        const __s16     DEAD_ZONE;
        const long int  VALUE;
    };

    struct TestGenerateHandlerUnique : public GenerateHandlerWithRangeUnique< TestGenerateHandlerUnique >
    {
        auto generateHandler(
            const Json::object_t &  _OBJECT
            , const __s16           _MIN
            , const __s16           _MAX
            , const __s16           _DEAD_ZONE
        ) const
        {
            const auto &    VALUE = _OBJECT.at( "key" ).get_ref< const Json::number_integer_t & >();

            return std::unique_ptr< TestHandler >(
                new TestHandler{
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , VALUE
                }
            );
        }
    };

    class GenerateHandlerWithRangeUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_MIN
            , const __s16       _EXPECTED_MAX
            , const __s16       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_MIN, handlerUnique->MIN );
            EXPECT_EQ( _EXPECTED_MAX, handlerUnique->MAX );
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
    GenerateHandlerWithRangeUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "key" : 40
})"
        , 10
        , 20
        , 30
        , 40
    );
}

TEST_F(
    GenerateHandlerWithRangeUniqueTest
    , FailedNotExistsMin
)
{
    this->testAnyThrow(
        R"({
    "max" : 20,
    "deadZone" : 30,
    "key" : 40
})"
    );
}

TEST_F(
    GenerateHandlerWithRangeUniqueTest
    , FailedNotIntegerMin
)
{
    this->testAnyThrow(
        R"({
    "min" : "NOT INTEGER",
    "max" : 20,
    "deadZone" : 30,
    "key" : 40
})"
    );
}

TEST_F(
    GenerateHandlerWithRangeUniqueTest
    , FailedNotExistsMax
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "deadZone" : 30,
    "key" : 40
})"
    );
}

TEST_F(
    GenerateHandlerWithRangeUniqueTest
    , FailedNotIntegerMax
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : "NOT INTEGER",
    "deadZone" : 30,
    "key" : 40
})"
    );
}

TEST_F(
    GenerateHandlerWithRangeUniqueTest
    , NotExistsDeadZone
)
{
    this->test(
        R"({
    "min" : 10,
    "max" : 20,
    "key" : 40
})"
        , 10
        , 20
        , 0
        , 40
    );
}

TEST_F(
    GenerateHandlerWithRangeUniqueTest
    , FailedNotUnsignedDeadZone
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : -30,
    "key" : 40
})"
    );
}
