#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <string>
#include <memory>

namespace {
    struct TestHandler_new
    {
        const __s16 MIN;
        const __s16 MAX;
        const __s16 DEAD_ZONE;
        const __s16 LIMIT;
    };

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

    using TestGenerateHandlerUnique_new = GenerateToAxisUnique_new< TestGenerateToAxisUnique_new >;

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

    //REMOVEME
    struct TestHandler
    {
        const __s16 DEAD_ZONE;
        const __s16 MAX;
    };

    //REMOVEME
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

    //REMOVEME
    using TestGenerateHandlerUnique = GenerateToAxisUnique< TestGenerateToAxisUnique >;

    //REMOVEME
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

//TODO FailedNotUnsignedLimit

//REMOVEME
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

//REMOVEME
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

//REMOVEME
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
