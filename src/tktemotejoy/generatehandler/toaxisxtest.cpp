#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToAxisXUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisXUnique_new( _OBJECT );
        }
    };

    using GenerateToAxisX_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisXUnique_new >;

    //REMOVEME
    struct GenerateToAxisXUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisXUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateToAxisXTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisXUnique >;
}

TEST_F(
    GenerateToAxisX_newTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisX",
    "min" : 100,
    "max" : 200,
    "deadZone" : 10,
    "limit" : 20
})"
        , 200
        , 0x80ff0000
    );
}

//REMOVEME
TEST_F(
    GenerateToAxisXTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisX",
    "deadZone" : 10,
    "max" : 20
})"
        , 20
        , 0x80ff0000
    );
}
