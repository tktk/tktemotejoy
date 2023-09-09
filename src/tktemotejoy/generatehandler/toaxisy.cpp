#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
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
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _LIMIT
        ) const
        {
            return Mapping::handlerUnique(
                new ToAxisY_old(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , ToAxisYImpl( _LIMIT )
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
        , GenerateToAxisUnique_old< GenerateToAxisYUnique >
    >( _OBJECT );
}
