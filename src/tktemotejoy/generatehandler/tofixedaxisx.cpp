#include "tktemotejoy/generatehandler/tofixedaxisx.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tofixedaxis.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <string>

namespace {
    const auto  TYPE = std::string( "toFixedAxisX" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateToFixedAxisXUnique
    {
        auto operator()(
            const __s16 _VALUE
        ) const
        {
            return Mapping::handlerUnique( new ToFixedAxisX( _VALUE ) );
        }
    };
}

Mapping::PressButtonHandlerForPspStateUnique generateToFixedAxisXUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::PressButtonHandlerForPspStateUnique
        , GetType
        , GenerateToFixedAxisUnique< GenerateToFixedAxisXUnique >
    >( _OBJECT );
}
