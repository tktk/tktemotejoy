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

    struct TestGenerateHandlerUniqueWithArgs
    {
        auto operator()(
            const Json::object_t &
            , const int &           _VALUE
        ) const
        {
            return TestHandlerUnique( new TestHandler{ _VALUE } );
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
        const __s32             MIN;
        const __s32             MAX;
        const __s32             DEAD_ZONE;
        const TestHandlerUnique HANDLER_MINUS_UNIQUE;
        const TestHandlerUnique HANDLER_PLUS_UNIQUE;
    };

    struct TestGenerateToButtonHandlersUnique
    {
        auto operator()(
            const __s32             _MIN
            , const __s32           _MAX
            , const __s32           _DEAD_ZONE
            , TestHandlerUnique &&  _handlerMinusUnique
            , TestHandlerUnique &&  _handlerPlusUnique
        ) const
        {
            return std::unique_ptr< TestToButtonHandlers >(
                new TestToButtonHandlers{
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , std::move( _handlerMinusUnique )
                    , std::move( _handlerPlusUnique )
                }
            );
        }
    };

    using TestGenerateHandlerUnique_ = GenerateToButtonHandlersUnique<
        TestGenerateToButtonHandlersUnique
        , TestGenerateHandlerUnique
        , TestGenerateDummyHandlerUnique
    >;

    using TestGenerateHandlerUniqueWithArgs_ = GenerateToButtonHandlersUnique<
        TestGenerateToButtonHandlersUnique
        , TestGenerateHandlerUniqueWithArgs
        , TestGenerateDummyHandlerUnique
    >;

    class GenerateToButtonHandlersUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s32       _EXPECTED_MIN
            , const __s32       _EXPECTED_MAX
            , const __s32       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_HANDLER_MINUS_VALUE
            , const int         _EXPECTED_HANDLER_PLUS_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_MIN, handlerUnique->MIN );
            EXPECT_EQ( _EXPECTED_MAX, handlerUnique->MAX );
            EXPECT_EQ( _EXPECTED_DEAD_ZONE, handlerUnique->DEAD_ZONE );
            ASSERT_NE( nullptr, handlerUnique->HANDLER_MINUS_UNIQUE.get() );
            EXPECT_EQ( _EXPECTED_HANDLER_MINUS_VALUE, handlerUnique->HANDLER_MINUS_UNIQUE->VALUE );
            ASSERT_NE( nullptr, handlerUnique->HANDLER_PLUS_UNIQUE.get() );
            EXPECT_EQ( _EXPECTED_HANDLER_PLUS_VALUE, handlerUnique->HANDLER_PLUS_UNIQUE->VALUE );
        }

        void testWithArgs(
            const std::string & _JSON_STRING
            , const int         _ARG_VALUE
            , const __s32       _EXPECTED_MIN
            , const __s32       _EXPECTED_MAX
            , const __s32       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_HANDLER_MINUS_VALUE
            , const int         _EXPECTED_HANDLER_PLUS_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUniqueWithArgs_()(
                OBJECT
                , _ARG_VALUE
            );
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
    GenerateToButtonHandlersUniqueTest
    , WithArgs
)
{
    this->testWithArgs(
        R"({
    "min" : 10,
    "max" : 20,
    "deadZone" : 30,
    "handlerMinus" : {
    },
    "handlerPlus" : {
    }
})"
        , 40
        , 10
        , 20
        , 30
        , 40
        , 40
    );
}

TEST_F(
    GenerateToButtonHandlersUniqueTest
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
    GenerateToButtonHandlersUniqueTest
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
    GenerateToButtonHandlersUniqueTest
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
    GenerateToButtonHandlersUniqueTest
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
    GenerateToButtonHandlersUniqueTest
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
    GenerateToButtonHandlersUniqueTest
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
