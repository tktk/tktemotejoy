#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/tobuttonhandlersforchangemapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <sstream>
#include <string>
#include <stdexcept>

Mapping::OperateAxisHandlerForChangeMappingUnique generateOperateAxisHandlerForChangeMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::OperateAxisHandlerForChangeMappingUnique();

    return handlerUnique;
    //TODO
/*
    handlerUnique = generateShiftMappingUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToggleMappingUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    auto    oStringStream = std::ostringstream();

    const auto  KEY_TYPE = std::string( "type" );

    oStringStream << "非対応のbuttonsForChangeMappingハンドラ : " << '"' << _OBJECT.at( KEY_TYPE ).get_ref< const Json::string_t & >() << '"';

    throw std::runtime_error( oStringStream.str() );
*/
}
