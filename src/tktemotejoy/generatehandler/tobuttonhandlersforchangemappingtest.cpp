#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlersForChangeMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generateToButtonHandlersForChangeMappingUnique_new(
                _OBJECT
                , _MAPPING_NAMES
            );
        }
    };

    using GenerateToButtonHandlersForChangeMapping_newTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlersForChangeMappingUnique_new >;
}

TEST_F(
    GenerateToButtonHandlersForChangeMapping_newTest
    , HandlerMinus
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
        , 50
        , 2
        , 50
    );
}

TEST_F(
    GenerateToButtonHandlersForChangeMapping_newTest
    , HandlerPlus
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
        , 192
        , 50
        , 3
        , 50
    );
}

TEST_F(
    GenerateToButtonHandlersForChangeMapping_newTest
    , NotExistsHandler
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "min" : 0,
    "max" : 255,
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
        , 50
        , 50
        , 50
    );
}
