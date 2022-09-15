#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    //FIXME
    struct GenerateToButtonHandlersForChangeMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForChangeMappingUnique_new( _OBJECT );
        }
    };

    //FIXME
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
        "mapping" : 20
    },
    "handlerPlus" : {
        "type" : "toggleMapping",
        "mapping" : 30
    }
})"
        , 64
        , 50
        , 20
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
        "mapping" : 20
    },
    "handlerPlus" : {
        "type" : "toggleMapping",
        "mapping" : 30
    }
})"
        , 192
        , 50
        , 30
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
        "mapping" : 30
    }
})"
        , 64
        , 50
        , 50
        , 50
    );
}
