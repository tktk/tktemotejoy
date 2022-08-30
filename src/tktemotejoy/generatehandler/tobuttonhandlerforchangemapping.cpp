#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandler.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandler.h"
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

    struct GenerateToButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const __u16                                             _DEAD_ZONE
            , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handlerUnique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlerForChangeMapping(
                    _DEAD_ZONE
                    , ToButtonHandlerForChangeMappingImpl( std::move( _handlerUnique ) )
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
}

Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlerForChangeMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForChangeMappingUnique
        , GetType
        , GenerateToButtonHandlerUnique<
            GenerateToButtonHandlerForChangeMappingUnique
            , GeneratePressButtonHandlerForChangeMappingUnique
        >
    >( _OBJECT );
}