#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/forpspstatetest.h"
#include "tktemotejoy/generatehandler/tobuttons.h"
#include "tktemotejoy/customjson.h"

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
    , NotMatchType
)
{
    this->testNull(
        R"({
    "buttons" : [
        "up"
    ]
})"
    );
}

TEST_F(
    GenerateToButtonsTest
    , Up
)
{
    this->test(
        R"({
    "type" : "toButtons",
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
    "type" : "toButtons",
    "buttons" : [
        "down"
    ]
})"
        , 0x80800040
    );
}

TEST_F(
    GenerateToButtonsTest
    , Left
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "left"
    ]
})"
        , 0x80800080
    );
}

TEST_F(
    GenerateToButtonsTest
    , Right
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "right"
    ]
})"
        , 0x80800020
    );
}

TEST_F(
    GenerateToButtonsTest
    , Circle
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "circle"
    ]
})"
        , 0x80802000
    );
}

TEST_F(
    GenerateToButtonsTest
    , Cross
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "cross"
    ]
})"
        , 0x80804000
    );
}

TEST_F(
    GenerateToButtonsTest
    , Triangle
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "triangle"
    ]
})"
        , 0x80801000
    );
}

TEST_F(
    GenerateToButtonsTest
    , Square
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "square"
    ]
})"
        , 0x80808000
    );
}

TEST_F(
    GenerateToButtonsTest
    , TriggerL
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "triggerL"
    ]
})"
        , 0x80800100
    );
}

TEST_F(
    GenerateToButtonsTest
    , TriggerR
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "triggerR"
    ]
})"
        , 0x80800200
    );
}

TEST_F(
    GenerateToButtonsTest
    , Start
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "start"
    ]
})"
        , 0x80800008
    );
}

TEST_F(
    GenerateToButtonsTest
    , Select
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "select"
    ]
})"
        , 0x80800001
    );
}

TEST_F(
    GenerateToButtonsTest
    , Buttons
)
{
    this->test(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "up",
        "up",
        "circle"
    ]
})"
        , 0x80802010
    );
}

TEST_F(
    GenerateToButtonsTest
    , IllegalButton
)
{
    this->testAnyThrow(
        R"({
    "type" : "toButtons",
    "buttons" : [
        "illegal"
    ]
})"
    );
}

TEST_F(
    GenerateToButtonsTest
    , NotExistsButtons
)
{
    this->testAnyThrow(
        R"({
    "type" : "toButtons",
    "button" : [
        "up"
    ]
})"
    );
}

TEST_F(
    GenerateToButtonsTest
    , ButtonsIsNotArray
)
{
    this->testAnyThrow(
        R"({
    "type" : "toButtons",
    "buttons" : "up"
})"
    );
}
