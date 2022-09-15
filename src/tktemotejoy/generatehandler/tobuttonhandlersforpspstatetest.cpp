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
    , HandlerMinus
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "min" : 0,
    "max" : 255,
    "handlerMinus" : {
        "type" : "toButtons",
        "buttons" : [
            "up"
        ]
    },
    "handlerPlus" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , 64
        , 0x80800010
    );
}

TEST_F(
    GenerateToButtonHandlersForPspStateTest
    , HandlerPlus
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "min" : 0,
    "max" : 255,
    "handlerMinus" : {
        "type" : "toButtons",
        "buttons" : [
            "up"
        ]
    },
    "handlerPlus" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , 192
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
    "min" : 0,
    "max" : 255,
    "handlerPlus" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , 64
        , 0
    );
}
