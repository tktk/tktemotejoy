#include "tktemotejoy/generatehandler/tobuttonhandlersforpspstate.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>

namespace {
    const auto  TYPE = std::string( "toButtonHandlers" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateToButtonHandlersForPspStateUnique
    {
        auto operator()(
            const __s16                                         _DEAD_ZONE
            , Mapping::PressButtonHandlerForPspStateUnique &&   _handler1Unique
            , Mapping::PressButtonHandlerForPspStateUnique &&   _handler2Unique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlersForPspState(
                    _DEAD_ZONE
                    , ToButtonHandlersForPspStateImpl(
                        std::move( _handler1Unique )
                        , std::move( _handler2Unique )
                    )
                )
            );
        }
    };
}

Mapping::OperateAxisHandlerForPspStateUnique generateToButtonHandlersForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    //TODO
    return Mapping::OperateAxisHandlerForPspStateUnique();
/*
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForPspStateUnique
        , GetType
        , GenerateToAxisUnique< GenerateToAxisXUnique >
    >( _OBJECT );
*/
}
