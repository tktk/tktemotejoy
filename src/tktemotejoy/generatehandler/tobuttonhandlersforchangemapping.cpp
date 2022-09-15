#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandlers.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandlers.h"
#include "tktemotejoy/handler/forchangemapping/dummy.h"
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

    struct GenerateToButtonHandlersForChangeMappingUnique
    {
        auto operator()(
            const __s16                                             _MIN
            , const __s16                                           _MAX
            , const __s16                                           _DEAD_ZONE
            , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handlerMinusUnique
            , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handlerPlusUnique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlersForChangeMapping(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , ToButtonHandlersForChangeMappingImpl(
                        std::move( _handlerMinusUnique )
                        , std::move( _handlerPlusUnique )
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
