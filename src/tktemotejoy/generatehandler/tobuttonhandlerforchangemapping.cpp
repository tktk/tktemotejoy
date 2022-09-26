#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/tobuttonhandler.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandler.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
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

    struct GenerateToButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const __s32                                             _MIN
            , const __s32                                           _MAX
            , const __s32                                           _DEAD_ZONE
            , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handlerUnique
        ) const
        {
            return Mapping::handlerUnique(
                new ToButtonHandlerForChangeMapping(
                    _MIN
                    , _MAX
                    , _DEAD_ZONE
                    , ToButtonHandlerForChangeMappingImpl( std::move( _handlerUnique ) )
                )
            );
        }
    };

    struct GeneratePressButtonHandlerForChangeMappingUnique_new
    {
        auto operator()(
            const Json::object_t &  _OBJECT
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique(
                _OBJECT
                , _MAPPING_NAMES
            );
        }
    };
}

Mapping::OperateAxisHandlerForChangeMappingUnique generateToButtonHandlerForChangeMappingUnique_new(
    const Json::object_t &  _OBJECT
    , const MappingNames &  _MAPPING_NAMES
)
{
    return generateHandlerUnique<
        Mapping::OperateAxisHandlerForChangeMappingUnique
        , GetType
        , GenerateToButtonHandlerUnique<
            GenerateToButtonHandlerForChangeMappingUnique
            , GeneratePressButtonHandlerForChangeMappingUnique_new
        >
    >(
        _OBJECT
        , _MAPPING_NAMES
    );
}
