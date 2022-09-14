#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlersForPspStateUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForPspStateUnique_new( _OBJECT );
        }
    };

    using GenerateToButtonHandlersForPspState_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlersForPspStateUnique_new >;

    //REMOVEME
    struct GenerateToButtonHandlersForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForPspStateUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateToButtonHandlersForPspStateTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToButtonHandlersForPspStateUnique >;
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

//REMOVEME
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

//REMOVEME
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

//REMOVEME
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
