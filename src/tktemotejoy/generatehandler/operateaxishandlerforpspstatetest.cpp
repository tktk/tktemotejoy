#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateOperateAxisHandlerForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateOperateAxisHandlerForPspStateUnique( _OBJECT );
        }
    };

    using GenerateOperateAxisHandlerForPspStateTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateOperateAxisHandlerForPspStateUnique >;
}

TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , ToAxisX
)
{
    this->test(
        R"({
    "type" : "toAxisX",
    "min" : 0,
    "max" : 255
})"
        , 192
        , 0x80c00000
    );
}

TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , ToAxisY
)
{
    this->test(
        R"({
    "type" : "toAxisY",
    "min" : 0,
    "max" : 255
})"
        , 192
        , 0xc0800000
    );
}

TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , ToButtonHandlers
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

//FIXME
TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , ToButtonHandler
)
{
    this->test(
        R"({
    "type" : "toButtonHandler",
    "deadZone" : 10000,
    "handler" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , -10000
        , 0x80800040
    );
}

TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , NotOperateAxisHandlerForPspState
)
{
    this->testNull(
        R"({
    "type" : "NOT OPERATE AXIS HANDLER"
})"
    );
}
