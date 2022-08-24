#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GeneratePressButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json &    _JSON
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique( _JSON );
        }
    };

    using GeneratePressButtonHandlerForChangeMappingTest = GeneratePressButtonHandlerForChangeMappingTestTmpl< GeneratePressButtonHandlerForChangeMappingUnique >;
}

TEST_F(
    GeneratePressButtonHandlerForChangeMappingTest
    , ShiftMapping
)
{
    this->test(
        R"({
    "type" : "shiftMapping",
    "mapping" : 10
})"
        , 20
        , 20
        , 10
    );
}

//TODO ToggleMapping
//TODO
/*
TEST_F(
    GeneratePressButtonHandlerForChangeMappingTest
    , NotPressButtonHandlerForChangeMapping
)
{
    this->testAnyThrow(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
    );
}
*/
