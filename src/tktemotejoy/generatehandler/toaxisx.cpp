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

    //FIXME
    struct GenerateToAxisXUnique_new
    {
        auto operator()(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _LIMIT
        ) const
        {
            return Mapping::handlerUnique(
                new ToAxisX(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , ToAxisXImpl( _LIMIT )
                )
            );
        }
    };
}

//FIXME
Mapping::OperateAxisHandlerForPspStateUnique generateToAxisXUnique_new(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForPspStateUnique
        , GetType
        , GenerateToAxisUnique_new< GenerateToAxisXUnique_new >
    >( _OBJECT );
}
