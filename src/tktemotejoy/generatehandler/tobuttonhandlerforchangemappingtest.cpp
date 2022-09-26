#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlerForChangeMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generateToButtonHandlerForChangeMappingUnique_new(
                _OBJECT
                , _MAPPING_NAMES
            );
        }
    };

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
        "mapping" : "mapping3"
    }
})"
        , {
            "mapping1",
            "mapping2",
            "mapping3",
            "mapping4",
            "mapping5",
        }
        , -25000
        , 10
        , 2
        , 10
    );
}
