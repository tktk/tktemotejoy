#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <string>
#include <memory>

namespace {
    //FIXME
    struct TestHandler_new
    {
        const __s16 MIN;
        const __s16 MAX;
        const __s16 DEAD_ZONE;
        const __s16 LIMIT;
    };

    //FIXME
    struct TestGenerateToAxisUnique_new
    {
        auto operator()(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _LIMIT
        ) const
        {
            return std::unique_ptr< TestHandler_new >(
                new TestHandler_new{
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , _LIMIT
                }
            );
        }
    };

    //FIXME
    using TestGenerateHandlerUnique_new = GenerateToAxisUnique_new< TestGenerateToAxisUnique_new >;

    //FIXME
    class GenerateToAxisUnique_newTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_MIN
            , const __s16       _EXPECTED_MAX
            , const __s16       _EXPECTED_DEAD_ZONE
            , const __s16       _EXPECTED_LIMIT
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_new()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_MIN, handlerUnique->MIN );
            EXPECT_EQ( _EXPECTED_MAX, handlerUnique->MAX );
            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            EXPECT_EQ( _EXPECTED_LIMIT, handlerUnique->LIMIT );
        }

        void testAnyThrow(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            EXPECT_ANY_THROW( TestGenerateHandlerUnique_new()( OBJECT ) );
        }
    };
}

TEST_F(
    GenerateToAxisUnique_newTest
    , Standard
)
{
    this->test(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "limit" : 40
})"
        , 10
        , 20
        , 30
        , 40
    );
}

TEST_F(
    GenerateToAxisUnique_newTest
    , NotExistsLimitMaxGreaterThanMin
)
{
    this->test(
        R"({
    "min" : 0,
    "max" : 255,
    "deadZone" : 30
})"
        , 0
        , 255
        , 30
        , 128
    );
}

TEST_F(
    GenerateToAxisUnique_newTest
    , NotExistsLimitMaxLesserThanMin
)
{
    this->test(
        R"({
    "min" : 255,
    "max" : 0,
    "deadZone" : 30
})"
        , 255
        , 0
        , 30
        , 128
    );
}

TEST_F(
    GenerateToAxisUnique_newTest
    , FailedNotUnsignedLimit
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "limit" : -40
})"
    );
}
