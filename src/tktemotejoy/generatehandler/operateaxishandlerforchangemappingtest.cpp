#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateOperateAxisHandlerForChangeMappingUnique_new
    {
        auto operator()(
            const Json &            _JSON
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generateOperateAxisHandlerForChangeMappingUnique_new(
                _JSON
                , _MAPPING_NAMES
            );
        }
    };

    using GenerateOperateAxisHandlerForChangeMapping_newTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl_new< GenerateOperateAxisHandlerForChangeMappingUnique_new >;
}

TEST_F(
    GenerateOperateAxisHandlerForChangeMapping_newTest
    , ToButtonHandlers
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "min" : 0,
    "max" : 255,
    "handlerMinus" : {
        "type" : "toggleMapping",
        "mapping" : "mapping3"
    },
    "handlerPlus" : {
        "type" : "toggleMapping",
        "mapping" : "mapping4"
    }
})"
        , {
            "mapping1",
            "mapping2",
            "mapping3",
            "mapping4",
            "mapping5",
        }
        , 64
        , 10
        , 2
        , 10
    );
}

TEST_F(
    GenerateOperateAxisHandlerForChangeMapping_newTest
    , ToButtonHandler
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

TEST_F(
    GenerateOperateAxisHandlerForChangeMapping_newTest
    , NotOperateAxisHandlerForChangeMapping
)
{
    this->testNull(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
        , {}
    );
}
