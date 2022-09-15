#include "tktemotejoy/generatehandler/tobuttonhandlersforpspstate.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandlers.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandlers.h"
#include "tktemotejoy/handler/forpspstate/dummy.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
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
            const __s16                                         _MIN
            , const __s16                                       _MAX
            , const __s16                                       _DEAD_ZONE
            , Mapping::PressButtonHandlerForPspStateUnique &&   _handlerMinusUnique
            , Mapping::PressButtonHandlerForPspStateUnique &&   _handlerPlusUnique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlersForPspState(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , ToButtonHandlersForPspStateImpl(
                        std::move( _handlerMinusUnique )
                        , std::move( _handlerPlusUnique )
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
