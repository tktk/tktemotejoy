#include "tktemotejoy/test.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/evdevstate.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    class GenerateMappings_mappingsTest : public ::testing::Test
    {
    public:
        void test(
            const std::string &     _JSON_STRING
            , const EvdevState &    _EVDEV_STATE
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            const auto  JSON = Json::parse( _JSON_STRING );

            auto    mappings = generateMappings(
                JSON
                , 20
                , 20
            );

            auto    pspState = PspState();

            mappings.evdevStateToPspState(
                pspState
                , _EVDEV_STATE
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

            EXPECT_ANY_THROW(
                generateMappings(
                    JSON
                    , 20
                    , 20
                )
            );
        }
    };
}

TEST_F(
    GenerateMappings_mappingsTest
    , ButtonsForPspState
)
{
    auto    evdevState = EvdevState(
        20
        , 20
    );

    evdevState.setButtonState(
        10
        , 1
    );

    this->test(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForPspState" : {
                "10" : {
                    "type" : "toButtons",
                    "buttons" : [
                        "up"
                    ]
                }
            }
        }
    }
})"
        , evdevState
        , 0x80800010
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , ButtonsForChangeMapping
)
{
    auto    evdevState = EvdevState(
        20
        , 20
    );

    evdevState.setButtonState(
        10
        , 1
    );

    this->test(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForChangeMapping" : {
                "10" : {
                    "type" : "shiftMapping",
                    "mapping" : "mapping2"
                }
            }
        },
        "mapping2" : {
            "buttonsForPspState" : {
                "10" : {
                    "type" : "toButtons",
                    "buttons" : [
                        "up"
                    ]
                }
            }
        }
    }
})"
        , evdevState
        , 0x80800010
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , AxesForPspState
)
{
    auto    evdevState = EvdevState(
        20
        , 20
    );

    evdevState.setAxisState(
        10
        , 192
    );

    this->test(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForPspState" : {
                "10" : {
                    "type" : "toAxisX",
                    "min" : 0,
                    "max" : 255
                }
            }
        }
    }
})"
        , evdevState
        , 0x80c00000
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , AxesForChangeMapping
)
{
    auto    evdevState = EvdevState(
        20
        , 20
    );

    evdevState.setAxisState(
        10
        , 192
    );

    this->test(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForChangeMapping" : {
                "10" : {
                    "type" : "toButtonHandlers",
                    "min" : 0,
                    "max" : 255,
                    "handlerPlus" : {
                        "type" : "shiftMapping",
                        "mapping" : "mapping2"
                    }
                }
            }
        },
        "mapping2" : {
            "axesForPspState" : {
                "10" : {
                    "type" : "toAxisX",
                    "min" : 0,
                    "max" : 255
                }
            }
        }
    }
})"
        , evdevState
        , 0x80c00000
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    }
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedNotObjectMappings
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : "NOT OBJECT"
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : "NOT OBJECT"
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForPspState" : "NOT OBJECT"
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForPspState" : {
                "NOT UNSIGNED" : {
                    "type" : "toButtons",
                    "buttons" : [
                        "up"
                    ]
                }
            }
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForPspState" : {
                "10" : "NOT OBJECT"
            }
        }
    }
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedUnsupportedHandlerMappingButtonsForPspStateElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping11" : {
            "buttonsForPspState" : {
                "10" : {
                    "type" : "UNSUPPORTED TYPE"
                }
            }
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForChangeMapping" : "NOT OBJECT"
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForChangeMapping" : {
                "NOT UNSIGNED" : {
                    "type" : "shiftMapping",
                    "mapping" : "mapping1"
                }
            }
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForChangeMapping" : {
                "10" : "NOT OBJECT"
            }
        }
    }
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedUnsupportedHandlerMappingButtonsForChangeMappingElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "buttonsForChangeMapping" : {
                "10" : {
                    "type" : "UNSUPPORTED TYPE"
                }
            }
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForPspState" : "NOT OBJECT"
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForPspState" : {
                "NOT UNSIGNED" : {
                    "type" : "toAxisX"
                }
            }
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForPspState" : {
                "10" : "NOT OBJECT"
            }
        }
    }
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedUnsupportedHandlerMappingAxesForPspStateElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForPspState" : {
                "10" : {
                    "type" : "UNSUPPORTED TYPE"
                }
            }
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForChangeMapping" : "NOT OBJECT"
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForChangeMapping" : {
                "NOT UNSIGNED" : {
                    "type" : "toButtonHandlers",
                    "min" : 0,
                    "max" : 255,
                    "handlerPlus" : {
                        "type" : "shiftMapping",
                        "mapping" : "mapping1"
                    }
                }
            }
        }
    }
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
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForChangeMapping" : {
                "10" : "NOT OBJECT"
            }
        }
    }
})"
    );
}

TEST_F(
    GenerateMappings_mappingsTest
    , FailedUnsupportedHandlerMappingAxesForChangeMappingElement
)
{
    this->testAnyThrow(
        R"({
    "general" : {
        "defaultMapping" : 10, "REMOVEME" : 0,
        "defaultMapping_new" : "mapping1"
    },
    "mappings_new" : {
        "mapping1" : {
            "axesForChangeMapping" : {
                "10" : {
                    "type" : "UNSUPPORTED TYPE"
                }
            }
        }
    }
})"
    );
}
