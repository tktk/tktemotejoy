#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/mappingnames.h"

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

    //REMOVEME
    struct GenerateShiftMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateShiftMappingUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateShiftMappingTest = GeneratePressButtonHandlerForChangeMappingTestTmpl< GenerateShiftMappingUnique >;
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

//REMOVEME
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
