#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToAxisXUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisXUnique( _OBJECT );
        }
    };

    using GenerateToAxisXTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisXUnique >;
}

TEST_F(
    GenerateToAxisXTest
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
