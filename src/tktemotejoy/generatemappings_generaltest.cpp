#include "tktemotejoy/test.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <array>

namespace {
    union TestMappings
    {
        struct
        {
            std::array< char, sizeof( Mappings::Impl ) > impl;
            Mappings::Impl::size_type   mappingIndex;
        };
        Mappings  mappings;
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

            auto    mappings = generateMappings(
                JSON
                , 0
                , 0
            );

            const auto &    TEST_MAPPINGS = reinterpret_cast< const TestMappings & >( mappings );

            EXPECT_EQ( _EXPECTED_MAPPING_INDEX, TEST_MAPPINGS.mappingIndex );
        }

        void testAnyThrow(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            EXPECT_ANY_THROW(
                generateMappings(
                    JSON
                    , 0
                    , 0
                )
            );
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
    , FailedNotExistsGeneral
)
{
    this->testAnyThrow(
        R"({
    "mappings" : []
})"
    );
}

TEST_F(
    GenerateMappings_generalTest
    , FailedNotObjectGeneral
)
{
    this->testAnyThrow(
        R"({
    "general" : [],
    "mappings" : []
})"
    );
}

TEST_F(
    GenerateMappings_generalTest
    , FailedNotExistsDefaultMapping
)
{
    this->testAnyThrow(
        R"({
    "general" : {},
    "mappings" : []
})"
    );
}

TEST_F(
    GenerateMappings_generalTest
    , FailedNotUnsignedDefaultMapping
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : -10
    },
    "mappings" : []
})"
    );
}
