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
    GenerateOperateAxisHandlerForChangeMappingTest
    , ToButtonHandler
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
