#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandlers.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandlers.h"
#include "tktemotejoy/handler/forchangemapping/dummy.h"
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

    struct GenerateToButtonHandlersForChangeMappingUnique
    {
        auto operator()(
            const __s16                                             _DEAD_ZONE
            , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handler1Unique
            , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handler2Unique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlersForChangeMapping(
                    _DEAD_ZONE
                    , ToButtonHandlersForChangeMappingImpl(
                        std::move( _handler1Unique )
                        , std::move( _handler2Unique )
                    )
                )
            );
        }
    };

    struct GeneratePressButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique( _OBJECT );
        }
    };

    struct GenerateDummyPressButtonHandlerForChangeMappingUnique
    {
        auto operator()(
        ) const
        {
            return Mapping::handlerUnique( new DummyPressButtonHandlerForChangeMapping() );
        }
    };
}

Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlersForChangeMappingUnique_new(
    const Json::object_t &  _OBJECT
)
{
    //TODO
    return Mapping::OperateAxisHandlerForChangeMappingUnique();
/*
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForChangeMappingUnique
        , GetType
        , GenerateToButtonHandlersUnique<
            GenerateToButtonHandlersForChangeMappingUnique
            , GeneratePressButtonHandlerForChangeMappingUnique
            , GenerateDummyPressButtonHandlerForChangeMappingUnique
        >
    >( _OBJECT );
*/
}

//REMOVEME
Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlersForChangeMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForChangeMappingUnique
        , GetType
        , GenerateToButtonHandlersUnique<
            GenerateToButtonHandlersForChangeMappingUnique
            , GeneratePressButtonHandlerForChangeMappingUnique
            , GenerateDummyPressButtonHandlerForChangeMappingUnique
        >
    >( _OBJECT );
}
