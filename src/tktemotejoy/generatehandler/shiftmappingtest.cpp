#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateShiftMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generateShiftMappingUnique_new(
                _OBJECT
                , _MAPPING_NAMES
            );
        }
    };

    using GenerateShiftMapping_newTest = GeneratePressButtonHandlerForChangeMappingTestTmpl_new< GenerateShiftMappingUnique_new >;
}

TEST_F(
    GenerateShiftMapping_newTest
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
