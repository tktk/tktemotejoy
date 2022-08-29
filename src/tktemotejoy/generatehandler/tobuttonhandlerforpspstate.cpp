#include "tktemotejoy/generatehandler/tobuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandler.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/handler/forpspstate/tobuttonhandler.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/joystick.h>
#include <string>

namespace {
    const auto  TYPE = std::string( "toButtonHandler" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateToButtonHandlerForPspStateUnique
    {
        auto operator()(
            const __s16                                         _DEAD_ZONE
            , Mapping::PressButtonHandlerForPspStateUnique &&   _handlerUnique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlerForPspState(
                    _DEAD_ZONE
                    , ToButtonHandlerForPspStateImpl( std::move( _handlerUnique ) )
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
}

Mapping::OperateAxisHandlerForPspStateUnique generateToButtonHandlerForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    //TODO
    return Mapping::OperateAxisHandlerForPspStateUnique();
/*
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForPspStateUnique
        , GetType
        , GenerateToButtonHandlersUnique<
            GenerateToButtonHandlerForPspStateUnique
            , GeneratePressButtonHandlerForPspStateUnique
        >
    >( _OBJECT );
*/
}
