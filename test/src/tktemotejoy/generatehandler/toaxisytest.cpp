#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToAxisYUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisYUnique( _OBJECT );
        }
    };

    using GenerateToAxisYTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisYUnique >;
}

TEST_F(
    GenerateToAxisYTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisY",
    "min" : 100,
    "max" : 200,
    "deadZone" : 10,
    "limit" : 50,
    "eraseDeadZone" : 64
})"
        , 175
        , 0xe0800000
    );
}
