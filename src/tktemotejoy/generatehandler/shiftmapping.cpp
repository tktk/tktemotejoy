#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/generatehandler/generatehandlerunique.h"
#include "tktemotejoy/generatehandler/changemapping.h"
#include "tktemotejoy/handler/forchangemapping/shiftmapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <cstddef>
#include <string>

namespace {
    const auto  TYPE = std::string( "shiftMapping" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateShiftMappingUnique
    {
        auto operator()(
            const std::size_t   _MAPPING_INDEX
        ) const
        {
            return Mapping::handlerUnique( new ShiftMapping( _MAPPING_INDEX ) );
        }
    };
}

Mapping::PressButtonHandlerForChangeMappingUnique generateShiftMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    //TODO
    return Mapping::PressButtonHandlerForChangeMappingUnique();
/*
    return generateHandlerUnique<
        Mapping::PressButtonHandlerForChangeMappingUnique
        , GetType
        , GenerateToFixedAxisUnique< GenerateShiftMappingUnique >
    >( _OBJECT );
*/
}
