#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlersForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForChangeMappingUnique( _OBJECT );
        }
    };

    using GenerateToButtonHandlersForChangeMappingTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlersForChangeMappingUnique >;
}

TEST_F(
    GenerateToButtonHandlersForChangeMappingTest
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
    GenerateToButtonHandlersForChangeMappingTest
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
    GenerateToButtonHandlersForChangeMappingTest
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
