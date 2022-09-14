#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToButtonHandlersForChangeMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForChangeMappingUnique_new( _OBJECT );
        }
    };

    using GenerateToButtonHandlersForChangeMapping_newTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlersForChangeMappingUnique_new >;

    //REMOVEME
    struct GenerateToButtonHandlersForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToButtonHandlersForChangeMappingUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateToButtonHandlersForChangeMappingTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateToButtonHandlersForChangeMappingUnique >;
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

//REMOVEME
TEST_F(
    GenerateToButtonHandlersForChangeMappingTest
    , Handler1
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "deadZone" : 10,
    "handler1" : {
        "type" : "toggleMapping",
        "mapping" : 20
    },
    "handler2" : {
        "type" : "toggleMapping",
        "mapping" : 30
    }
})"
        , -40
        , 50
        , 20
        , 50
    );
}

//REMOVEME
TEST_F(
    GenerateToButtonHandlersForChangeMappingTest
    , Handler2
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "deadZone" : 10,
    "handler1" : {
        "type" : "toggleMapping",
        "mapping" : 20
    },
    "handler2" : {
        "type" : "toggleMapping",
        "mapping" : 30
    }
})"
        , 40
        , 50
        , 30
        , 50
    );
}

//REMOVEME
TEST_F(
    GenerateToButtonHandlersForChangeMappingTest
    , NotExistsHandler
)
{
    this->test(
        R"({
    "type" : "toButtonHandlers",
    "deadZone" : 10,
    "handler2" : {
        "type" : "toggleMapping",
        "mapping" : 30
    }
})"
        , -40
        , 50
        , 50
        , 50
    );
}
