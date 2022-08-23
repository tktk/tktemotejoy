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
    "deadZone" : 10,
    "max" : 20
})"
        , 20
        , 0x80ff0000
    );
}
