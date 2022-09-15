#include "tktemotejoy/test.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/evdevstate.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    class GenerateMappingsTest : public ::testing::Test
    {
    public:
        void test(
            const std::string & _JSON_STRING
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            auto    mappings = generateMappings(
                JSON
                , 10
                , 20
            );

            auto    pspState = PspState();

            const auto  EVDEV_STATE = EvdevState(
                10
                , 20
            );

            mappings.evdevStateToPspState(
                pspState
                , EVDEV_STATE
            );
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
    GenerateMappingsTest
    , Minimum
)
{
    this->test(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappingsTest
    , NotObject
)
{
    this->testAnyThrow( R"("NOT OBJECT")" );
}

TEST_F(
    GenerateMappingsTest
    , FailedGenerateGeneral
)
{
    this->testAnyThrow(
        R"({
    "mappings" : [
        {
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappingsTest
    , FailedGenerateMappingsImpl
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    }
})"
    );
}
