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
