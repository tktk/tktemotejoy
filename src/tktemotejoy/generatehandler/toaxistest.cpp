#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <string>
#include <memory>

namespace {
    struct TestHandler
    {
        const __s32 MIN;
        const __s32 MAX;
        const __s32 DEAD_ZONE;
        const __s32 LIMIT;
        const __s32 ERASE_DEAD_ZONE;
    };

    struct TestGenerateToAxisUnique
    {
        auto operator()(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _LIMIT
            , const __s32   _ERASE_DEAD_ZONE
        ) const
        {
            return std::unique_ptr< TestHandler >(
                new TestHandler{
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , _LIMIT
                    , _ERASE_DEAD_ZONE
                }
            );
        }
    };

    using TestGenerateHandlerUnique = GenerateToAxisUnique< TestGenerateToAxisUnique >;

    class GenerateToAxisUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s32       _EXPECTED_MIN
            , const __s32       _EXPECTED_MAX
            , const __s32       _EXPECTED_DEAD_ZONE
            , const __s32       _EXPECTED_LIMIT
            , const __s32       _EXPECTED_ERASE_DEAD_ZONE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_MIN, handlerUnique->MIN );
            EXPECT_EQ( _EXPECTED_MAX, handlerUnique->MAX );
            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            EXPECT_EQ( _EXPECTED_LIMIT, handlerUnique->LIMIT );
            EXPECT_EQ( _EXPECTED_ERASE_DEAD_ZONE, handlerUnique->ERASE_DEAD_ZONE );
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
    GenerateToAxisUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "limit" : 40,
    "eraseDeadZone" : 50
})"
        , 10
        , 20
        , 30
        , 40
        , 50
    );
}

TEST_F(
    GenerateToAxisUniqueTest
    , NotExistsLimitMaxGreaterThanMin
)
{
    this->test(
        R"({
    "min" : 0,
    "max" : 255,
    "deadZone" : 30,
    "eraseDeadZone" : 50
})"
        , 0
        , 255
        , 30
        , 128
        , 50
    );
}

TEST_F(
    GenerateToAxisUniqueTest
    , NotExistsLimitMaxLesserThanMin
)
{
    this->test(
        R"({
    "min" : 255,
    "max" : 0,
    "deadZone" : 30,
    "eraseDeadZone" : 50
})"
        , 255
        , 0
        , 30
        , 128
        , 50
    );
}

TEST_F(
    GenerateToAxisUniqueTest
    , NotExistsEraseDeadZone
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
        , 0
    );
}

TEST_F(
    GenerateToAxisUniqueTest
    , FailedNotUnsignedLimit
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "limit" : -40,
    "eraseDeadZone" : 50
})"
    );
}

TEST_F(
    GenerateToAxisUniqueTest
    , FailedNotUnsignedEraseDeadZone
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "limit" : 40,
    "eraseDeadZone" : -50
})"
    );
}
