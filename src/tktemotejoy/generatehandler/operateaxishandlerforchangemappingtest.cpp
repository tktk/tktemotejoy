#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateOperateAxisHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json &    _JSON
        ) const
        {
            return generateOperateAxisHandlerForChangeMappingUnique( _JSON );
        }
    };

    using GenerateOperateAxisHandlerForChangeMappingTest = GenerateOperateAxisHandlerForChangeMappingTestTmpl< GenerateOperateAxisHandlerForChangeMappingUnique >;
}

TEST_F(
    GenerateOperateAxisHandlerForChangeMappingTest
    , ToButtonHandlers
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
    GenerateOperateAxisHandlerForChangeMappingTest
    , ToButtonHandler
)
{
    this->test(
        R"({
    "type" : "toButtonHandler",
    "deadZone" : 50000,
    "handler" : {
        "type" : "toggleMapping",
        "mapping" : 10
    }
})"
        , 60000
        , 20
        , 10
        , 20
    );
}

TEST_F(
    GenerateOperateAxisHandlerForChangeMappingTest
    , NotOperateAxisHandlerForChangeMapping
)
{
    this->testNull(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
    );
}
