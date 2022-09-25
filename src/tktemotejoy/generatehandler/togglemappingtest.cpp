#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/togglemapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToggleMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generateToggleMappingUnique_new(
                _OBJECT
                , _MAPPING_NAMES
            );
        }
    };

    using GenerateToggleMapping_newTest = GeneratePressButtonHandlerForChangeMappingTestTmpl_new< GenerateToggleMappingUnique_new >;

    //REMOVEME
    struct GenerateToggleMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToggleMappingUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateToggleMappingTest = GeneratePressButtonHandlerForChangeMappingTestTmpl< GenerateToggleMappingUnique >;
}

TEST_F(
    GenerateToggleMapping_newTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toggleMapping",
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
        , 2
        , 10
    );
}

//REMOVEME
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
