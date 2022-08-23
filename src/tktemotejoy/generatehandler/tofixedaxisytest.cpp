#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tofixedaxisy.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToFixedAxisYUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToFixedAxisYUnique( _OBJECT );
        }
    };

    using GenerateToFixedAxisYTest = GeneratePressButtonHandlerForPspStateTestTmpl< GenerateToFixedAxisYUnique >;
}

TEST_F(
    GenerateToFixedAxisYTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toFixedAxisY",
    "value" : 32767
})"
        , 0xff800000
    );
}
