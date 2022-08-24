#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlers.h"
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

    struct TestGenerateDummyHandlerUnique
    {
        auto operator()(
        ) const
        {
            return TestHandlerUnique( new TestHandler{ -1 } );
        }
    };

    struct TestToButtonHandlers
    {
        const __s16             DEAD_ZONE;
        const TestHandlerUnique HANDLER1_UNIQUE;
        const TestHandlerUnique HANDLER2_UNIQUE;
    };

    struct TestGenerateToButtonHandlersUnique
    {
        auto operator()(
            const __s16             _DEAD_ZONE
            , TestHandlerUnique &&  _handler1Unique
            , TestHandlerUnique &&  _handler2Unique
        ) const
        {
            return std::unique_ptr< TestToButtonHandlers >(
                new TestToButtonHandlers{
                    _DEAD_ZONE
                    , std::move( _handler1Unique )
                    , std::move( _handler2Unique )
                }
            );
        }
    };

    using TestGenerateHandlerUnique_ = GenerateToButtonHandlersUnique<
        TestGenerateToButtonHandlersUnique
        , TestGenerateHandlerUnique
        , TestGenerateDummyHandlerUnique
    >;

    class GenerateToButtonHandlersUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_HANDLER1_VALUE
            , const int         _EXPECTED_HANDLER2_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            ASSERT_NE( nullptr, handlerUnique->HANDLER1_UNIQUE.get() );
            EXPECT_EQ( _EXPECTED_HANDLER1_VALUE, handlerUnique->HANDLER1_UNIQUE->VALUE );
            ASSERT_NE( nullptr, handlerUnique->HANDLER2_UNIQUE.get() );
            EXPECT_EQ( _EXPECTED_HANDLER2_VALUE, handlerUnique->HANDLER2_UNIQUE->VALUE );
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
    GenerateToButtonHandlersUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "deadZone" : 10,
    "handler1" : {
        "key" : 20
    },
    "handler2" : {
        "key" : 30
    }
})"
        , 10
        , 20
        , 30
    );
}

TEST_F(
    GenerateToButtonHandlersUniqueTest
    , NotExistsHandler1
)
{
    this->test(
        R"({
    "deadZone" : 10,
    "handler2" : {
        "key" : 30
    }
})"
        , 10
        , -1
        , 30
    );
}

TEST_F(
    GenerateToButtonHandlersUniqueTest
    , NotExistsHandler2
)
{
    this->test(
        R"({
    "deadZone" : 10,
    "handler1" : {
        "key" : 20
    }
})"
        , 10
        , 20
        , -1
    );
}

//TODO
/*
TEST_F(
    GenerateToButtonHandlersUniqueTest
    , FailedNotObjectHandler1
)
{
    this->testAnyThrow(
        R"({
    "deadZone" : 10,
    "max" : "NOT INTEGER"
})"
    );
}
*/

//TODO FailedNotObjectHandler2
