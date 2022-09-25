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

    using GenerateToButtonHandlerForChangeMapping_newTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl_new< GenerateToButtonHandlerForChangeMappingUnique_new >;

    //REMOVEME
    struct GenerateToButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForChangeMappingUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateToButtonHandlerForChangeMappingTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlerForChangeMappingUnique >;
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

//REMOVEME
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
