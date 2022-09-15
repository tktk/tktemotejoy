#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlerForChangeMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlerForChangeMappingUnique_new( _OBJECT );
        }
    };

    using GenerateToButtonHandlerForChangeMapping_newTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlerForChangeMappingUnique_new >;

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
        "mapping" : 10
    }
})"
        , -25000
        , 20
        , 10
        , 20
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
    "deadZone" : 10000,
    "handler" : {
        "type" : "toggleMapping",
        "mapping" : 10
    }
})"
        , -10000
        , 20
        , 10
        , 20
    );
}
