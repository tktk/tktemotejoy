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

//TODO ToButtonHandler

TEST_F(
    GenerateOperateAxisHandlerForChangeMappingTest
    , FailedNotOperateAxisHandlerForChangeMapping
)
{
    this->testAnyThrow(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
    );
}
