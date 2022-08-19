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

TEST_F(
    GenerateToButtonsTest
    , Left
)
{
    this->test(
        R"({
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
    "button" : [
        "up"
    ]
})"
    );
}

//TODO ButtonsIsNotArray
