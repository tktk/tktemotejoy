#include "tktemotejoy/test.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>

namespace {
    union TestMappings
    {
        struct
        {
            std::array< char, sizeof( Mappings::Impl ) >    impl;
            Mappings::Impl::size_type                       mappingIndex;
        };
        Mappings  mappings;
    };

    auto getMappingIndex(
        const Json &            _JSON
        , const std::string &   _MAPPING_NAME
    )
    {
        const auto &    ROOT = _JSON.get_ref< const Json::object_t & >();
        const auto &    MAPPINGS = ROOT.at( "mappings" ).get_ref< const Json::object_t & >();

        auto    keys = std::vector< std::string >();
        for( const auto & PAIR : MAPPINGS ) {
            keys.push_back( PAIR.first );
        }

        const auto  KEYS_BEGIN = keys.begin();
        const auto  IT = std::lower_bound(
            KEYS_BEGIN
            , keys.end()
            , _MAPPING_NAME
        );

        const auto  MAPPING_INDEX = std::distance(
            KEYS_BEGIN
            , IT
        );

        return MAPPING_INDEX;
    }

    class GenerateMappings_generalTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &     _JSON_STRING
            , const std::string &   _MAPPING_NAME
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            const auto  EXPECTED_MAPPING_INDEX = getMappingIndex(
                JSON
                , _MAPPING_NAME
            );

            auto    mappings = generateMappings(
                JSON
                , 0
                , 0
            );

            const auto &    TEST_MAPPINGS = reinterpret_cast< const TestMappings & >( mappings );

            EXPECT_EQ( EXPECTED_MAPPING_INDEX, TEST_MAPPINGS.mappingIndex );
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
        "defaultMapping" : "mapping3"
    },
    "mappings" : {
        "mapping1" : {},
        "mapping2" : {},
        "mapping3" : {},
        "mapping4" : {},
        "mapping5" : {}
    }
})"
        , "mapping3"
    );
}

TEST_F(
    GenerateMappings_generalTest
    , FailedNotExistsGeneral
)
{
    this->testAnyThrow(
        R"({
    "mappings" : {}
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
    "mappings" : {}
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
    "mappings" : {}
})"
    );
}

TEST_F(
    GenerateMappings_generalTest
    , FailedNotStringDefaultMapping
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 10
    },
    "mappings" : {}
})"
    );
}

TEST_F(
    GenerateMappings_generalTest
    , FailedDefaultMappingIsNotMappingName
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : "notExists"
    },
    "mappings" : {
        "mapping1" : {},
        "mapping2" : {},
        "mapping3" : {},
        "mapping4" : {},
        "mapping5" : {}
    }
})"
    );
}
