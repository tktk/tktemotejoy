#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    //FIXME
    struct GenerateToAxisYUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisYUnique_new( _OBJECT );
        }
    };

    //FIXME
    using GenerateToAxisY_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisYUnique_new >;
}

TEST_F(
    GenerateToAxisY_newTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisY",
    "min" : 100,
    "max" : 200,
    "deadZone" : 10,
    "limit" : 50
})"
        , 175
        , 0xc0800000
    );
}
