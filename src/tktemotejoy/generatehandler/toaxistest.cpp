#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <string>
#include <memory>

//REMOVEME
namespace {
    struct TestHandler_old
    {
        const __s32 MIN;
        const __s32 MAX;
        const __s32 DEAD_ZONE;
        const __s32 LIMIT;
    };

    struct TestGenerateToAxisUnique_old
    {
        auto operator()(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _LIMIT
        ) const
        {
            return std::unique_ptr< TestHandler_old >(
                new TestHandler_old{
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , _LIMIT
                }
            );
        }
    };

    using TestGenerateHandlerUnique_old = GenerateToAxisUnique_old< TestGenerateToAxisUnique_old >;

    class GenerateToAxisUnique_oldTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s32       _EXPECTED_MIN
            , const __s32       _EXPECTED_MAX
            , const __s32       _EXPECTED_DEAD_ZONE
            , const __s32       _EXPECTED_LIMIT
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_old()( OBJECT );
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

            EXPECT_ANY_THROW( TestGenerateHandlerUnique_old()( OBJECT ) );
        }
    };
}

//REMOVEME
TEST_F(
    GenerateToAxisUnique_oldTest
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

//REMOVEME
TEST_F(
    GenerateToAxisUnique_oldTest
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

//REMOVEME
TEST_F(
    GenerateToAxisUnique_oldTest
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

//REMOVEME
TEST_F(
    GenerateToAxisUnique_oldTest
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
