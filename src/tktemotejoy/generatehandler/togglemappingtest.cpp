#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/togglemapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToggleMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToggleMappingUnique( _OBJECT );
        }
    };

    using GenerateToggleMappingTest = GeneratePressButtonHandlerForChangeMappingTestTmpl< GenerateToggleMappingUnique >;
}

TEST_F(
    GenerateToggleMappingTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toggleMapping",
    "mapping" : 10
})"
        , 20
        , 10
        , 20
    );
}
