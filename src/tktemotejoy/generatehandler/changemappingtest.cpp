#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/changemapping.h"
#include "tktemotejoy/customjson.h"
#include <cstddef>
#include <string>
#include <memory>

namespace {
    struct TestHandler
    {
        const std::size_t   MAPPING_INDEX;
    };

    struct TestGenerateChangeMappingUnique
    {
        auto operator()(
            const std::size_t   _MAPPING_INDEX
        ) const
        {
            return std::unique_ptr< TestHandler >(
                new TestHandler{
                    _MAPPING_INDEX
                }
            );
        }
    };

    using TestGenerateHandlerUnique = GenerateChangeMappingUnique< TestGenerateChangeMappingUnique >;

    class GenerateChangeMappingUniqueTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
            , const std::size_t _EXPECTED_MAPPING_INDEX
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique()( OBJECT );

            ASSERT_NE( nullptr, handlerUnique.get() );
            EXPECT_EQ( _EXPECTED_MAPPING_INDEX, handlerUnique->MAPPING_INDEX );
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
    GenerateChangeMappingUniqueTest
    , Standard
)
{
    this->test(
        R"({
    "mapping" : 10
})"
        , 10
    );
}

TEST_F(
    GenerateChangeMappingUniqueTest
    , FailedNotExistsMapping
)
{
    this->testAnyThrow(
        R"({
})"
    );
}

TEST_F(
    GenerateChangeMappingUniqueTest
    , FailedNotIntegerMapping
)
{
    this->testAnyThrow(
        R"({
    "mapping" : "NOT INTEGER"
})"
    );
}
