#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    //FIXME
    struct GenerateToButtonHandlerForPspStateUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForPspStateUnique_new( _OBJECT );
        }
    };

    //FIXME
    using GenerateToButtonHandlerForPspState_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlerForPspStateUnique_new >;
}

TEST_F(
    GenerateToButtonHandlerForPspState_newTest
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
