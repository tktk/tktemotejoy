#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForChangeMappingUnique( _OBJECT );
        }
    };

    using GenerateToButtonHandlerForChangeMappingTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlerForChangeMappingUnique >;
}

TEST_F(
    GenerateToButtonHandlerForChangeMappingTest
    , Handler
)
{
    this->test(
        R"({
    "type" : "toButtonHandler",
    "min" : 0,
    "max" : -30000,
    "deadZone" : 20000,
    "handler" : {
        "type" : "toggleMapping",
        "mapping" : 10
    }
})"
        , -25000
        , 20
        , 10
        , 20
    );
}
