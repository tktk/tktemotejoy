#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>
#include <memory>

namespace {
    struct TestHandler
    {
        const __s16 DEAD_ZONE;
        const __s16 MAX;
    };

    struct TestGenerateToAxisUnique
    {
        auto operator()(
            const __s16     _DEAD_ZONE
            , const __s16   _MAX
        ) const
        {
            return std::unique_ptr< TestHandler >(
                new TestHandler{
                    _DEAD_ZONE
                    , _MAX
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
            , const __s16       _EXPECTED_DEAD_ZONE
            , const __s16       _EXPECTED_MAX
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            EXPECT_EQ( _EXPECTED_MAX, handlerUnique->MAX );
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
    "deadZone" : 10,
    "max" : 20
})"
        , 10
        , 20
    );
}

TEST_F(
    GenerateToAxisUniqueTest
    , NotExistsMax
)
{
    this->test(
        R"({
    "deadZone" : 10
})"
        , 10
        , 32767
    );
}

TEST_F(
    GenerateToAxisUniqueTest
    , FailedNotIntegerMax
)
{
    this->testAnyThrow(
        R"({
    "deadZone" : 10,
    "max" : "NOT INTEGER"
})"
    );
}
