#include "tktemotejoy/test.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/joystickstate.h"
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

            auto    mappings = generateMappings( JSON );

            auto    pspState = PspState();

            const auto  JOYSTICK_STATE = JoystickState(
                10
                , 20
            );

            mappings.joystickStateToPspState(
                pspState
                , JOYSTICK_STATE
            );
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
    },
})"
    );
}
