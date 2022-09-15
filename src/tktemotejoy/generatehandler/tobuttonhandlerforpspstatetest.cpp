#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlerForPspStateUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForPspStateUnique_new( _OBJECT );
        }
    };

    using GenerateToButtonHandlerForPspState_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlerForPspStateUnique_new >;

    //REMOVEME
    struct GenerateToButtonHandlerForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForPspStateUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateToButtonHandlerForPspStateTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlerForPspStateUnique >;
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

//REMOVEME
TEST_F(
    GenerateToButtonHandlerForPspStateTest
    , Handler
)
{
    this->test(
        R"({
    "type" : "toButtonHandler",
    "deadZone" : 10000,
    "handler" : {
        "type" : "toButtons",
        "buttons" : [
            "up"
        ]
    }
})"
        , -10000
        , 0x80800010
    );
}
