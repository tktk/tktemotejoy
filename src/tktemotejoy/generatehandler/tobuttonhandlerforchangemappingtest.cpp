#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    //FIXME
    struct GenerateToButtonHandlerForChangeMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForChangeMappingUnique_new( _OBJECT );
        }
    };

    //FIXME
    using GenerateToButtonHandlerForChangeMapping_newTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlerForChangeMappingUnique_new >;
}

TEST_F(
    GenerateToButtonHandlerForChangeMapping_newTest
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
