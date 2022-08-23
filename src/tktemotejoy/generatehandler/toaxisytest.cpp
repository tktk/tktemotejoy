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
    "deadZone" : 10,
    "max" : 20
})"
        , 20
        , 0xff800000
    );
}
