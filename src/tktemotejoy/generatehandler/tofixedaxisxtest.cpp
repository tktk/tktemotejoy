#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tofixedaxisx.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToFixedAxisXUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToFixedAxisXUnique( _OBJECT );
        }
    };

    using GenerateToFixedAxisXTest = GeneratePressButtonHandlerForPspStateTestTmpl< GenerateToFixedAxisXUnique >;
}

TEST_F(
    GenerateToFixedAxisXTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toFixedAxisX",
    "value" : 32767
})"
        , 0x80ff0000
    );
}
