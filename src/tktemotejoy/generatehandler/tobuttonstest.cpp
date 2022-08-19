#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/forpspstatetest.h"
#include "tktemotejoy/generatehandler/tobuttons.h"
#include "nlohmann/json.hpp"

namespace {
    struct GenerateToButtonsUnique
    {
        auto operator()(
            const Json &    _JSON
        ) const
        {
            return generateToButtonsUnique( _JSON );
        }
    };

    using GenerateToButtonsTest = GenerateHandlerForPspStateTest< GenerateToButtonsUnique >;
}

TEST_F(
    GenerateToButtonsTest
    , Up
)
{
    this->test(
        R"({
    "buttons" : [
        "up"
    ]
})"
        , 0x80800010
    );
}

TEST_F(
    GenerateToButtonsTest
    , Down
)
{
    this->test(
        R"({
    "buttons" : [
        "down"
    ]
})"
        , 0x80800040
    );
}

//TODO Left
//TODO Right
//TODO Circle
//TODO Cross
//TODO Triangle
//TODO Square
//TODO TriggerL
//TODO TriggerR
//TODO Start
//TODO Select
//TODO Buttons
//TODO IllegalButton
//TODO NotExistsButtons
//TODO ButtonsIsNotArray
