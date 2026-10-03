#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateShiftMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generateShiftMappingUnique(
                _OBJECT
                , _MAPPING_NAMES
            );
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
    "mapping" : "mapping3"
})"
        , {
            "mapping1",
            "mapping2",
            "mapping3",
            "mapping4",
            "mapping5",
        }
        , 10
        , 10
        , 2
    );
}
