#include "tktemotejoy/test.h"
#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstatetest.h"
#include "tktemotejoy/customjson.h"

namespace {
    struct GenerateToAxisYUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisYUnique_new( _OBJECT );
        }
    };

    using GenerateToAxisY_newTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisYUnique_new >;

    //REMOVEME
    struct GenerateToAxisYUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateToAxisYUnique( _OBJECT );
        }
    };

    //REMOVEME
    using GenerateToAxisYTest = GenerateOperateAxisHandlerForPspStateTestTmpl< GenerateToAxisYUnique >;
}

TEST_F(
    GenerateToAxisY_newTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisY",
    "min" : 100,
    "max" : 200,
    "deadZone" : 10,
    "limit" : 50
})"
        , 175
        , 0xc0800000
    );
}

//REMOVEME
TEST_F(
    GenerateToAxisYTest
    , Standard
)
{
    this->test(
        R"({
    "type" : "toAxisY",
    "deadZone" : 10,
    "max" : 20
})"
        , 20
        , 0xff800000
    );
}
