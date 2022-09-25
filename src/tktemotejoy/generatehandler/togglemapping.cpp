#include "tktemotejoy/generatehandler/togglemapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/changemapping.h"
#include "tktemotejoy/handler/forchangemapping/togglemapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"
#include <cstddef>
#include <string>

namespace {
    const auto  TYPE = std::string( "toggleMapping" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateToggleMappingUnique
    {
        auto operator()(
            const std::size_t   _MAPPING_INDEX
        ) const
        {
            return Mapping::handlerUnique( new ToggleMapping( _MAPPING_INDEX ) );
        }
    };
}

Mapping::PressButtonHandlerForChangeMappingUnique generateToggleMappingUnique_new(
    const Json::object_t &  _OBJECT
    , const MappingNames &  _MAPPING_NAMES
)
{
    return generateHandlerUnique<
        Mapping::PressButtonHandlerForChangeMappingUnique
        , GetType
        , GenerateChangeMappingUnique_new< GenerateToggleMappingUnique >
    >(
        _OBJECT
        , _MAPPING_NAMES
    );
}

//REMOVEME
Mapping::PressButtonHandlerForChangeMappingUnique generateToggleMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    return generateHandlerUnique<
        Mapping::PressButtonHandlerForChangeMappingUnique
        , GetType
        , GenerateChangeMappingUnique< GenerateToggleMappingUnique >
    >( _OBJECT );
}
