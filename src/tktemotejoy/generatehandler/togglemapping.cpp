#include "tktemotejoy/generatehandler/togglemapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/changemapping.h"
#include "tktemotejoy/handler/forchangemapping/togglemapping.h"
#include "tktemotejoy/mapping.h"
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

Mapping::PressButtonHandlerForChangeMappingUnique generateToggleMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    //TODO
    return Mapping::PressButtonHandlerForChangeMappingUnique();
/*
    return generateHandlerUnique<
        Mapping::PressButtonHandlerForChangeMappingUnique
        , GetType
        , GenerateChangeMappingUnique< GenerateToggleMappingUnique >
    >( _OBJECT );
*/
}
