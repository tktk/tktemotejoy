#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    //FIXME
    struct GenerateToAxisXUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisXUnique_new( _OBJECT );
        }
    };

    //FIXME
    using GenerateToAxisX_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisXUnique_new >;
}

TEST_F(
    GenerateToAxisX_newTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisX",
    "min" : 100,
    "max" : 200,
    "deadZone" : 10,
    "limit" : 50
})"
        , 175
        , 0x80c00000
    );
}
