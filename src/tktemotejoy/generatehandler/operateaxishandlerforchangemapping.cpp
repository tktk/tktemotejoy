#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/generatehandler/tobuttonhandlerforchangemapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/typeerror.h"
#include <string>
#include <stdexcept>

Mapping::OperateAxisHandlerForChangeMappingUnique generateOperateAxisHandlerForChangeMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::OperateAxisHandlerForChangeMappingUnique();

    handlerUnique = generateToButtonHandlersForChangeMappingUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToButtonHandlerForChangeMappingUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    const auto  HANDLERS_TYPE = std::string( "axesForChangeMapping" );

    throw typeIsNotSupported(
        _OBJECT
        , HANDLERS_TYPE
    );
}
