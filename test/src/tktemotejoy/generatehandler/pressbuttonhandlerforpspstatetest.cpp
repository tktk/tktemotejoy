#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GeneratePressButtonHandlerForPspStateUnique
    {
        auto operator()(
            const Json &    _JSON
        ) const
        {
            return generatePressButtonHandlerForPspStateUnique( _JSON );
        }
    };

    using GeneratePressButtonHandlerForPspStateTest = GeneratePressButtonHandlerForPspStateTestTmpl< GeneratePressButtonHandlerForPspStateUnique >;
}

TEST_F(
    GeneratePressButtonHandlerForPspStateTest
    , ToButtons
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
    GeneratePressButtonHandlerForPspStateTest
    , ToFixedAxisX
)
{
    this->test(
        R"({
    "type" : "toFixedAxisX",
    "value" : 192
})"
        , 0x80c00000
    );
}

TEST_F(
    GeneratePressButtonHandlerForPspStateTest
    , ToFixedAxisY
)
{
    this->test(
        R"({
    "type" : "toFixedAxisY",
    "value" : 192
})"
        , 0xc0800000
    );
}

TEST_F(
    GeneratePressButtonHandlerForPspStateTest
    , NotPressButtonHandlerForPspState
)
{
    this->testNull(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
    );
}
