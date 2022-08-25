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
            "buttonsForPspState" : {
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

TEST_F(
    GenerateMappings_mappingsTest
    , ButtonsForChangeMapping
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
            "buttonsForChangeMapping" : {
                "10" : {
                    "type" : "shiftMapping",
                    "mapping" : 1
                }
            }
        },
        {
            "buttonsForPspState" : {
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
            "axesForPspState" : {
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

TEST_F(
    GenerateMappings_mappingsTest
    , AxesForChangeMapping
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
            "axesForChangeMapping" : {
                "10" : {
                    "type" : "toButtonHandlers",
                    "handler2" : {
                        "type" : "shiftMapping",
                        "mapping" : 1
                    }
                }
            }
        },
        {
            "axesForPspState" : {
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

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotExistsMappings
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

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotArrayMappings
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : "NOT ARRAY"
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingsElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        "NOT OBJECT"
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingButtonsForPspState
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "buttonsForPspState" : "NOT OBJECT"
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotUnsignedStringMappingButtonsForPspStateKey
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "buttonsForPspState" : {
                "NOT UNSIGNED" : {
                    "type" : "toButtons",
                    "buttons" : [
                        "up"
                    ]
                }
            }
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingButtonsForPspStateElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "buttonsForPspState" : {
                "10" : "NOT OBJECT"
            }
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingButtonsForChangeMapping
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "buttonsForChangeMapping" : "NOT OBJECT"
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotUnsignedStringMappingButtonsForChangeMappingKey
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "buttonsForChangeMapping" : {
                "NOT UNSIGNED" : {
                    "type" : "shiftMapping",
                    "mapping" : 1
                }
            }
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingButtonsForChangeMappingElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "buttonsForChangeMapping" : {
                "10" : "NOT OBJECT"
            }
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingAxesForPspState
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "axesForPspState" : "NOT OBJECT"
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotUnsignedStringMappingAxesForPspStateKey
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "axesForPspState" : {
                "NOT UNSIGNED" : {
                    "type" : "toAxisX"
                }
            }
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingAxesForPspStateElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "axesForPspState" : {
                "10" : "NOT OBJECT"
            }
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingAxesForChangeMapping
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "axesForChangeMapping" : "NOT OBJECT"
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotUnsignedStringMappingAxesForChangeMappingKey
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "axesForChangeMapping" : {
                "NOT UNSIGNED" : {
                    "type" : "toButtonHandlers",
                    "handler2" : {
                        "type" : "shiftMapping",
                        "mapping" : 1
                    }
                }
            }
        }
    ]
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappingAxesForChangeMappingElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 0
    },
    "mappings" : [
        {
            "axesForChangeMapping" : {
                "10" : "NOT OBJECT"
            }
        }
    ]
})"
    );
}
