#include "tktemotejoy/generatehandler/tobuttonhandlersforpspstate.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandlers.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/handler/forpspstate/dummy.h"
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

    struct GeneratePressButtonHandlerForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generatePressButtonHandlerForPspStateUnique( _OBJECT );
        }
    };

    struct GenerateDummyPressButtonHandlerForPspStateUnique
    {
        auto operator()(
        ) const
        {
            return Mapping::handlerUnique( new DummyPressButtonHandlerForPspState() );
        }
    };
}

Mapping::OperateAxisHandlerForPspStateUnique generateToButtonHandlersForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForPspStateUnique
        , GetType
        , GenerateToButtonHandlersUnique<
            GenerateToButtonHandlersForPspStateUnique
            , GeneratePressButtonHandlerForPspStateUnique
            , GenerateDummyPressButtonHandlerForPspStateUnique
        >
    >( _OBJECT );
}
