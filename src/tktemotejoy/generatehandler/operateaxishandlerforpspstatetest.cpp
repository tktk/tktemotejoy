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
    "type" : "toAxisX"
})"
        , 0x7fff
        , 0x80ff0000
    );
}

TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , ToAxisY
)
{
    this->test(
        R"({
    "type" : "toAxisY"
})"
        , 0x7fff
        , 0xff800000
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
        , 0x7fff
        , 0x80800040
    );
}

TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , ToButtonHandler
)
{
    this->test(
        R"({
    "type" : "toButtonHandler",
    "deadZone" : 60000,
    "handler" : {
        "type" : "toButtons",
        "buttons" : [
            "down"
        ]
    }
})"
        , 0xffff
        , 0x80800040
    );
}

TEST_F(
    GenerateOperateAxisHandlerForPspStateTest
    , FailedNotOperateAxisHandlerForPspState
)
{
    this->testAnyThrow(
        R"({
    "type" : "NOT OPERATE AXIS HANDLER"
})"
    );
}
