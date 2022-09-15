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
            const auto  IT = _OBJECT.find( "key" );
            if( IT == _OBJECT.end() ) {
                return TestHandlerUnique();
            }
            const auto &    VALUE = IT->second.get_ref< const Json::number_integer_t & >();

            return TestHandlerUnique( new TestHandler{ static_cast< const int >( VALUE ) } );
        }
    };

    struct TestToButtonHandler_new
    {
        const __s16             MIN;
        const __s16             MAX;
        const __s16             DEAD_ZONE;
        const TestHandlerUnique HANDLER_UNIQUE;
    };

    struct TestGenerateToButtonHandlerUnique_new
    {
        auto operator()(
            const __s16             _MIN
            , const __s16           _MAX
            , const __s16           _DEAD_ZONE
            , TestHandlerUnique &&  _handlerUnique
        ) const
        {
            return std::unique_ptr< TestToButtonHandler_new >(
                new TestToButtonHandler_new{
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , std::move( _handlerUnique )
                }
            );
        }
    };

    using TestGenerateHandlerUnique_new_ = GenerateToButtonHandlerUnique_new<
        TestGenerateToButtonHandlerUnique_new
        , TestGenerateHandlerUnique
    >;

    class GenerateToButtonHandlerUnique_newTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_MIN
            , const __s16       _EXPECTED_MAX
            , const __s16       _EXPECTED_DEAD_ZONE
            , const int         _EXPECTED_HANDLER_VALUE
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_new_()( OBJECT );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_MIN, handlerUnique->MIN );
            EXPECT_EQ( _EXPECTED_MAX, handlerUnique->MAX );
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

            EXPECT_ANY_THROW( TestGenerateHandlerUnique_new_()( OBJECT ) );
        }
    };

    //REMOVEME
    struct TestToButtonHandler
    {
        const __s16             DEAD_ZONE;
        const TestHandlerUnique HANDLER_UNIQUE;
    };

    //REMOVEME
    struct TestGenerateToButtonHandlerUnique
    {
        auto operator()(
            const __s16             _DEAD_ZONE
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

    //REMOVEME
    using TestGenerateHandlerUnique_ = GenerateToButtonHandlerUnique<
        TestGenerateToButtonHandlerUnique
        , TestGenerateHandlerUnique
    >;

    //REMOVEME
    class GenerateToButtonHandlerUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const __s16       _EXPECTED_DEAD_ZONE
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
    GenerateToButtonHandlerUnique_newTest
    , Standard
)
{
    this->test(
        R"({
    "min" : 0,
    "max" : 255,
    "deadZone" : 10,
    "handler" : {
        "key" : 20
    }
})"
        , 0
        , 255
        , 10
        , 20
    );
}

TEST_F(
    GenerateToButtonHandlerUnique_newTest
    , FailedNotExistsHandler
)
{
    this->testAnyThrow(
        R"({
    "min" : 0,
    "max" : 255,
    "deadZone" : 10
})"
    );
}

TEST_F(
    GenerateToButtonHandlerUnique_newTest
    , FailedNotObjectHandler
)
{
    this->testAnyThrow(
        R"({
    "min" : 0,
    "max" : 255,
    "deadZone" : 10,
    "handler" : "NOT OBJECT"
})"
    );
}

//TODO FailedUnsupportedHandler

//REMOVEME
TEST_F(
    GenerateToButtonHandlerUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "deadZone" : 10000,
    "handler" : {
        "key" : 20
    }
})"
        , -22767
        , 20
    );
}

//REMOVEME
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

//REMOVEME
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

//REMOVEME
TEST_F(
    GenerateToButtonHandlerUniqueTest
    , FailedUnsupportedHandler
)
{
    this->testAnyThrow(
        R"({
    "deadZone" : 10,
    "handler" : {
    }
})"
    );
}
