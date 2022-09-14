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

    struct GenerateToAxisYUnique_new
    {
        auto operator()(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _LIMIT
        ) const
        {
            return Mapping::handlerUnique(
                new ToAxisY_new(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , ToAxisY_newImpl( _LIMIT )
                )
            );
        }
    };

    //REMOVEME
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

Mapping::OperateAxisHandlerForPspStateUnique generateToAxisYUnique_new(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForPspStateUnique
        , GetType
        , GenerateToAxisUnique_new< GenerateToAxisYUnique_new >
    >( _OBJECT );
}

//REMOVEME
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
