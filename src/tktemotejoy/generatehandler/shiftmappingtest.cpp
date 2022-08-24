#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateShiftMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateShiftMappingUnique( _OBJECT );
        }
    };

    using GenerateShiftMappingTest = GeneratePressButtonHandlerForChangeMappingTestTmpl< GenerateShiftMappingUnique >;
}

TEST_F(
    GenerateShiftMappingTest
    , Standard
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
