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
    "value" : 32767
})"
        , 0x80ff0000
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
    "value" : 32767
})"
        , 0xff800000
    );
}

TEST_F(
    GeneratePressButtonHandlerForPspStateTest
    , NotPressButtonHandlerForPspState
)
{
    this->testAnyThrow(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
    );
}
