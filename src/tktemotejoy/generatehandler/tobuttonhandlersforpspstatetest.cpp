#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    //FIXME
    struct GenerateToButtonHandlersForPspStateUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForPspStateUnique_new( _OBJECT );
        }
    };

    //FIXME
    using GenerateToButtonHandlersForPspState_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlersForPspStateUnique_new >;
}

TEST_F(
    GenerateToButtonHandlersForPspState_newTest
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
    GenerateToButtonHandlersForPspState_newTest
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
    GenerateToButtonHandlersForPspState_newTest
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
