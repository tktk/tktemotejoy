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
    "deadZone" : 50000,
    "handler" : {
        "type" : "toButtons",
        "buttons" : [
            "up"
        ]
    }
})"
        , 60000 ^ 0x8000
        , 0x80800010
    );
}
