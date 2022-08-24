#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlersForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForPspStateUnique( _OBJECT );
        }
    };

    using GenerateToButtonHandlersForPspStateTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlersForPspStateUnique >;
}

TEST_F(
    GenerateToButtonHandlersForPspStateTest
    , Handler1
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "deadZone" : 10,
    "handler1" : {
        "type" : "toButtons",
        "buttons" : [
            "up"
        ]
    },
    "handler2" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , -20
        , 0x80800010
    );
}

TEST_F(
    GenerateToButtonHandlersForPspStateTest
    , Handler2
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "deadZone" : 10,
    "handler1" : {
        "type" : "toButtons",
        "buttons" : [
            "up"
        ]
    },
    "handler2" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , 20
        , 0x80800040
    );
}

TEST_F(
    GenerateToButtonHandlersForPspStateTest
    , NotExistsHandler
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "deadZone" : 10,
    "handler2" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , -20
        , 0
    );
}
