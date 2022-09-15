#include "tktemotejoy/generatehandler/tofixedaxisy.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tofixedaxis.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisy.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/customjson.h"
#include <string>

namespace {
    const auto  TYPE = std::string( "toFixedAxisY" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateToFixedAxisYUnique
    {
        auto operator()(
            const PspState::Axis    _VALUE
        ) const
        {
            return Mapping::handlerUnique( new ToFixedAxisY( _VALUE ) );
        }
    };
}

Mapping::PressButtonHandlerForPspStateUnique generateToFixedAxisYUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::PressButtonHandlerForPspStateUnique
        , GetType
        , GenerateToFixedAxisUnique< GenerateToFixedAxisYUnique >
    >( _OBJECT );
}
