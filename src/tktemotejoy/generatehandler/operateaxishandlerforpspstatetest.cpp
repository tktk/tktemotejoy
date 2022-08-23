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

//TODO ToButtonHandlers

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
