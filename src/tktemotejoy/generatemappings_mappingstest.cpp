#include "tktemotejoy/test.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/joystickstate.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    class GenerateMappings_mappingsTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &     _JSON_STRING
            , const JoystickState & _JOYSTICK_STATE
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            auto    mappings = generateMappings( JSON );

            auto    pspState = PspState();

            mappings.joystickStateToPspState(
                pspState
                , _JOYSTICK_STATE
            );

            const auto  OTHER = PspState();

            auto    bits = PspState::Bits();

            pspState.diff(
                OTHER
                , [
                    &bits
                ]
                (
                    const PspState::Bits &  _BITS
                )
                {
                    bits = _BITS;
                }
            );

            EXPECT_EQ( _EXPECTED_BITS, bits );
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
    GenerateMappings_mappingsTest
    , ButtonsForPspState
)
{
    auto    joystickState = JoystickState(
        20
        , 20
    );

    joystickState.setButtonState(
        10
        , 1
    );

    this->test(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "buttons" : {
                "10" : {
                    "type" : "toButtons",
                    "buttons" : [
                        "up"
                    ]
                }
            }
        }
    ]
})"
        , joystickState
        , 0x80800010
    );
}

//TODO ButtonsForChangeMapping

TEST_F(
    GenerateMappings_mappingsTest
    , AxesForPspState
)
{
    auto    joystickState = JoystickState(
        20
        , 20
    );

    joystickState.setAxisState(
        10
        , 0x7fff
    );

    this->test(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "axes" : {
                "10" : {
                    "type" : "toAxisX"
                }
            }
        }
    ]
})"
        , joystickState
        , 0x80ff0000
    );
}

//TODO AxesForChangeMapping
//TODO NotExistsMappings
//TODO MappingsIsNotArray
//TODO MappingsElementIsNotObject
//TODO MappingButtonsKeyIsNotInteger
//TODO MappingButtonsIsNotObject
//TODO MappingButtonsElementIsNotObject
//TODO MappingAxesKeyIsNotInteger
//TODO MappingAxesIsNotObject
//TODO MappingAxesElementIsNotObject
