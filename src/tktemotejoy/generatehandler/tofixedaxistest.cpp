#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tofixedaxis.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>
#include <memory>

namespace {
    struct TestHandler
    {
        const __s16 VALUE;
    };

    struct TestGenerateToFixedAxisUnique
    {
        auto operator()(
            const __s16 _VALUE
        ) const
        {
            return std::unique_ptr< TestHandler >(
                new TestHandler{
                    _VALUE
                }
            );
        }
    };

    using TestGenerateHandlerUnique = GenerateToFixedAxisUnique< TestGenerateToFixedAxisUnique >;

    class GenerateToFixedAxisUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique()( OBJECT );

            ASSERT_NE( nullptr, handlerUnique.get() );
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
    GenerateToFixedAxisUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "value" : 10
})"
        , 10
    );
}

TEST_F(
    GenerateToFixedAxisUniqueTest
    , FailedNotExistsValue
)
{
    this->testAnyThrow(
        R"({
})"
    );
}

TEST_F(
    GenerateToFixedAxisUniqueTest
    , FailedNotIntegerValue
)
{
    this->testAnyThrow(
        R"({
    "value" : "NOT INTEGER"
})"
    );
}
