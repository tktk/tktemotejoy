#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandler.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>
#include <memory>
#include <utility>

namespace {
    struct TestHandler
    {
        const int   VALUE;
    };

    using TestHandlerUnique = std::unique_ptr< TestHandler >;

    struct TestGenerateHandlerUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            const auto &    VALUE = _OBJECT.at( "key" ).get_ref< const Json::number_integer_t & >();

            return TestHandlerUnique( new TestHandler{ static_cast< const int >( VALUE ) } );
        }
    };

    struct TestToButtonHandler
    {
        const __u16             DEAD_ZONE;
        const TestHandlerUnique HANDLER_UNIQUE;
    };

    struct TestGenerateToButtonHandlerUnique
    {
        auto operator()(
            const __u16             _DEAD_ZONE
            , TestHandlerUnique &&  _handlerUnique
        ) const
        {
            return std::unique_ptr< TestToButtonHandler >(
                new TestToButtonHandler{
                    _DEAD_ZONE
                    , std::move( _handlerUnique )
                }
            );
        }
    };

    using TestGenerateHandlerUnique_ = GenerateToButtonHandlerUnique<
        TestGenerateToButtonHandlerUnique
        , TestGenerateHandlerUnique
    >;

    class GenerateToButtonHandlerUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __u16       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_HANDLER_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            ASSERT_NE( nullptr, handlerUnique->HANDLER_UNIQUE.get() );
            EXPECT_EQ( _EXPECTED_HANDLER_VALUE, handlerUnique->HANDLER_UNIQUE->VALUE );
        }

        void testAnyThrow(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            EXPECT_ANY_THROW( TestGenerateHandlerUnique_()( OBJECT ) );
        }
    };
}

TEST_F(
    GenerateToButtonHandlerUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "deadZone" : 10,
    "handler" : {
        "key" : 20
    }
})"
        , 10
        , 20
    );
}

TEST_F(
    GenerateToButtonHandlerUniqueTest
    , FailedNotExistsHandler
)
{
    this->testAnyThrow(
        R"({
    "deadZone" : 10
})"
    );
}

TEST_F(
    GenerateToButtonHandlerUniqueTest
    , FailedNotObjectHandler
)
{
    this->testAnyThrow(
        R"({
    "deadZone" : 10,
    "handler" : "NOT OBJECT"
})"
    );
}
