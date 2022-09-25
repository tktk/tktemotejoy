#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemappingtest.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GeneratePressButtonHandlerForChangeMappingUnique_new
    {
        auto operator()(
            const Json &            _JSON
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique_new(
                _JSON
                , _MAPPING_NAMES
            );
        }
    };

    using GeneratePressButtonHandlerForChangeMapping_newTest = GeneratePressButtonHandlerForChangeMappingTestTmpl_new< GeneratePressButtonHandlerForChangeMappingUnique_new >;

    //REMOVEME
    struct GeneratePressButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json &    _JSON
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique( _JSON );
        }
    };

    //REMOVEME
    using GeneratePressButtonHandlerForChangeMappingTest = GeneratePressButtonHandlerForChangeMappingTestTmpl< GeneratePressButtonHandlerForChangeMappingUnique >;
}

TEST_F(
    GeneratePressButtonHandlerForChangeMapping_newTest
    , ShiftMapping
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

TEST_F(
    GeneratePressButtonHandlerForChangeMapping_newTest
    , ToggleMapping
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

TEST_F(
    GeneratePressButtonHandlerForChangeMapping_newTest
    , NotPressButtonHandlerForChangeMapping
)
{
    this->testNull(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
        , {}
    );
}

//REMOVEME
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

//REMOVEME
TEST_F(
    GeneratePressButtonHandlerForChangeMappingTest
    , ToggleMapping
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

//REMOVEME
TEST_F(
    GeneratePressButtonHandlerForChangeMappingTest
    , NotPressButtonHandlerForChangeMapping
)
{
    this->testNull(
        R"({
    "type" : "NOT PRESS BUTTON HANDLER"
})"
    );
}
