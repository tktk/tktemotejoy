#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>

namespace {
    const auto  TYPE = std::string( "toAxisY" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateToAxisYUnique
    {
        auto operator()(
            const __s16     _DEAD_ZONE
            , const __s16   _MAX
        ) const
        {
            return Mapping::handlerUnique(
                new ToAxisY(
                    _DEAD_ZONE
                    , ToAxisYImpl( _MAX )
                )
            );
        }
    };
}

Mapping::OperateAxisHandlerForPspStateUnique generateToAxisYUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForPspStateUnique
        , GetType
        , GenerateToAxisUnique< GenerateToAxisYUnique >
    >( _OBJECT );
}
