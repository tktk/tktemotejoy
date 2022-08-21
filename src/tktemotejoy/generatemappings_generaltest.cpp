#include "tktemotejoy/test.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    struct TestMappings
    {
        const Mappings::Impl        IMPL;
        Mappings::Impl::size_type   mappingIndex;
    };

    class GenerateMappings_generalTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &                 _JSON_STRING
            , const Mappings::Impl::size_type   _EXPECTED_MAPPING_INDEX
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            auto    mappings = generateMappings( JSON );

            const auto &    TEST_MAPPINGS = reinterpret_cast< const TestMappings & >( mappings );

            EXPECT_EQ( _EXPECTED_MAPPING_INDEX, TEST_MAPPINGS.mappingIndex );
        }

        void testAnyThrow(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            EXPECT_ANY_THROW( generateMappings( JSON ) );
        }
    };
}

TEST_F(
    GenerateMappings_generalTest
    , Standard
)
{
    this->test(
        R"({
    "general" : {
        "defaultMapping" : 10
    },
    "mappings" : []
})"
        , 10
    );
}

TEST_F(
    GenerateMappings_generalTest
    , NotExistsGeneral
)
{
    this->testAnyThrow(
        R"({
    "mappings" : []
})"
    );
}

//TODO GeneralIsNotMap
//TODO NotExistsDefaultMapping
//TODO DefaultMappingIsNotUnsignedInteger
