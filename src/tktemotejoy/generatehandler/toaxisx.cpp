#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/toaxis.h"
#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
#include <string>

namespace {
    const auto  TYPE = std::string( "toAxisX" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateToAxisXUnique
    {
        auto operator()(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _LIMIT
            , const __s32   _ERASE_DEAD_ZONE
        ) const
        {
            return Mapping::handlerUnique(
                new ToAxisX(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , ToAxisXImpl(
                        _LIMIT
                        , _ERASE_DEAD_ZONE
                    )
                )
            );
        }
    };
}

Mapping::OperateAxisHandlerForPspStateUnique generateToAxisXUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForPspStateUnique
        , GetType
        , GenerateToAxisUnique< GenerateToAxisXUnique >
    >( _OBJECT );
}
