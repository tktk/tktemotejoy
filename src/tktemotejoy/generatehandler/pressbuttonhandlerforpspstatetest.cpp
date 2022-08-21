#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/forpspstatetest.h"
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

    using GeneratePressButtonHandlerForPspStateTest = GenerateHandlerForPspStateTest< GeneratePressButtonHandlerForPspStateUnique >;
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

//TODO ToFixedAxisX
//TODO ToFixedAxisY
//TODO HandlerIsNotForPspState
