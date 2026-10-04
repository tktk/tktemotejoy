#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlerForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForPspStateUnique( _OBJECT );
        }
    };

    using GenerateToButtonHandlerForPspStateTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlerForPspStateUnique >;
}

TEST_F(
    GenerateToButtonHandlerForPspStateTest
    , Handler
)
{
    this->test(
        R"({
    "type" : "toButtonHandler",
    "min" : 0,
    "max" : -30000,
    "deadZone" : 20000,
    "handler" : {
        "type" : "toButtons",
        "buttons" : [
            "up"
        ]
    }
})"
        , -25000
        , 0x80800010
    );
}
