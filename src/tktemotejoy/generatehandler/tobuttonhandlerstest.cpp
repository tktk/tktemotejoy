#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlers.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
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
            const auto  IT = _OBJECT.find( "key" );
            if( IT == _OBJECT.end() ) {
                return TestHandlerUnique();
            }
            const auto &    VALUE = IT->second.get_ref< const Json::number_integer_t & >();

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

    //FIXME
    struct TestToButtonHandlers_new
    {
        const __s16             MIN;
        const __s16             MAX;
        const __s16             DEAD_ZONE;
        const TestHandlerUnique HANDLER_MINUS_UNIQUE;
        const TestHandlerUnique HANDLER_PLUS_UNIQUE;
    };

    //FIXME
    struct TestGenerateToButtonHandlersUnique_new
    {
        auto operator()(
            const __s16             _MIN
            , const __s16           _MAX
            , const __s16           _DEAD_ZONE
            , TestHandlerUnique &&  _handlerMinusUnique
            , TestHandlerUnique &&  _handlerPlusUnique
        ) const
        {
            return std::unique_ptr< TestToButtonHandlers_new >(
                new TestToButtonHandlers_new{
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , std::move( _handlerMinusUnique )
                    , std::move( _handlerPlusUnique )
                }
            );
        }
    };

    //FIXME
    using TestGenerateHandlerUnique_new_ = GenerateToButtonHandlersUnique_new<
        TestGenerateToButtonHandlersUnique_new
        , TestGenerateHandlerUnique
        , TestGenerateDummyHandlerUnique
    >;

    //FIXME
    class GenerateToButtonHandlersUnique_newTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_MIN
            , const __s16       _EXPECTED_MAX
            , const __s16       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_HANDLER_MINUS_VALUE
            , const int         _EXPECTED_HANDLER_PLUS_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_new_()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_MIN, handlerUnique->MIN );
            EXPECT_EQ( _EXPECTED_MAX, handlerUnique->MAX );
            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            ASSERT_NE( nullptr, handlerUnique->HANDLER_MINUS_UNIQUE.get() );
            EXPECT_EQ( _EXPECTED_HANDLER_MINUS_VALUE, handlerUnique->HANDLER_MINUS_UNIQUE->VALUE );
            ASSERT_NE( nullptr, handlerUnique->HANDLER_PLUS_UNIQUE.get() );
            EXPECT_EQ( _EXPECTED_HANDLER_PLUS_VALUE, handlerUnique->HANDLER_PLUS_UNIQUE->VALUE );
        }

        void testAnyThrow(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            EXPECT_ANY_THROW( TestGenerateHandlerUnique_new_()( OBJECT ) );
        }
    };
}

TEST_F(
    GenerateToButtonHandlersUnique_newTest
    , Standard
)
{
    this->test(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerMinus" : {
        "key" : 40
    },
    "handlerPlus" : {
        "key" : 50
    }
})"
        , 10
        , 20
        , 30
        , 40
        , 50
    );
}

TEST_F(
    GenerateToButtonHandlersUnique_newTest
    , NotExistsHandlerMinus
)
{
    this->test(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerPlus" : {
        "key" : 50
    }
})"
        , 10
        , 20
        , 30
        , -1
        , 50
    );
}

TEST_F(
    GenerateToButtonHandlersUnique_newTest
    , FailedNotObjectHandlerMinus
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerMinus" : "NOT OBJECT",
    "handlerPlus" : {
        "key" : 50
    }
})"
    );
}

TEST_F(
    GenerateToButtonHandlersUnique_newTest
    , FailedUnsupportedHandlerMinus
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerMinus" : {
    },
    "handlerPlus" : {
        "key" : 50
    }
})"
    );
}

TEST_F(
    GenerateToButtonHandlersUnique_newTest
    , NotExistsHandlerPlus
)
{
    this->test(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerMinus" : {
        "key" : 40
    }
})"
        , 10
        , 20
        , 30
        , 40
        , -1
    );
}

TEST_F(
    GenerateToButtonHandlersUnique_newTest
    , FailedNotObjectHandlerPlus
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerMinus" : {
        "key" : 40
    },
    "handlerPlus" : "NOT OBJECT"
})"
    );
}

TEST_F(
    GenerateToButtonHandlersUnique_newTest
    , FailedUnsupportedHandlerPlus
)
{
    this->testAnyThrow(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerMinus" : {
        "key" : 40
    },
    "handlerPlus" : {
    }
})"
    );
}
