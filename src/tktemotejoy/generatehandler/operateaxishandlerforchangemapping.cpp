#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"

Mapping::OperateAxisHandlerForChangeMappingUnique generateOperateAxisHandlerForChangeMappingUnique(
    const Json::object_t &  _OBJECT
    , const MappingNames &  _MAPPING_NAMES
)
{
    auto    handlerUnique = Mapping::OperateAxisHandlerForChangeMappingUnique();

    handlerUnique = generateToButtonHandlersForChangeMappingUnique_new(
        _OBJECT
        , _MAPPING_NAMES
    );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToButtonHandlerForChangeMappingUnique_new(
        _OBJECT
        , _MAPPING_NAMES
    );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    return handlerUnique;
}
