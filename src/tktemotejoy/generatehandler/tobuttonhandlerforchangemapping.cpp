#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandler.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandler.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <linux/input.h>
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

    //FIXME
    struct GenerateToButtonHandlerForChangeMappingUnique_new
    {
        auto operator()(
            const __s16                                             _MIN
            , const __s16                                           _MAX
            , const __s16                                           _DEAD_ZONE
            , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handlerUnique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlerForChangeMapping_new(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
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

//FIXME
Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlerForChangeMappingUnique_new(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForChangeMappingUnique
        , GetType
        , GenerateToButtonHandlerUnique_new<
            GenerateToButtonHandlerForChangeMappingUnique_new
            , GeneratePressButtonHandlerForChangeMappingUnique
        >
    >( _OBJECT );
}
