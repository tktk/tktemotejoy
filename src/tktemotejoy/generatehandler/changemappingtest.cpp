#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/changemapping.h"
#include "tktemotejoy/mappingnames.h"
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

    using TestGenerateHandlerUnique_new = GenerateChangeMappingUnique_new< TestGenerateChangeMappingUnique >;

    class GenerateChangeMappingUnique_newTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &     _JSON_STRING
            , const MappingNames &  _MAPPING_NAMES
            , const std::size_t     _EXPECTED_MAPPING_INDEX
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = TestGenerateHandlerUnique_new()(
                OBJECT
                , _MAPPING_NAMES
            );
            ASSERT_NE( nullptr, handlerUnique.get() );

            EXPECT_EQ( _EXPECTED_MAPPING_INDEX, handlerUnique->MAPPING_INDEX );
        }

        void testAnyThrow(
            const std::string &     _JSON_STRING
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto &    OBJECT = JSON.get_ref< const Json::object_t & >();

            EXPECT_ANY_THROW(
                TestGenerateHandlerUnique_new()(
                    OBJECT
                    , _MAPPING_NAMES
                )
            );
        }
    };
}

TEST_F(
    GenerateChangeMappingUnique_newTest
    , Standard
)
{
    this->test(
        R"({
    "mapping" : "mapping3"
})"
        , {
            "mapping1",
            "mapping2",
            "mapping3",
            "mapping4",
            "mapping5",
        }
        , 2
    );
}

TEST_F(
    GenerateChangeMappingUnique_newTest
    , FailedNotExistsMapping
)
{
    this->testAnyThrow(
        R"({
})"
        , {}
    );
}

TEST_F(
    GenerateChangeMappingUnique_newTest
    , FailedNotStringMapping
)
{
    this->testAnyThrow(
        R"({
    "mapping" : 10
})"
        , {}
    );
}

TEST_F(
    GenerateChangeMappingUnique_newTest
    , FailedMappingIsNotMappingName
)
{
    this->testAnyThrow(
        R"({
    "mapping" : "notMappingName"
})"
        , {
            "mapping1",
            "mapping2",
            "mapping3",
            "mapping4",
            "mapping5",
        }
    );
}
