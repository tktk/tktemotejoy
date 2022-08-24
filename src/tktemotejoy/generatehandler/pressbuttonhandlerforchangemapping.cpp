#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/shiftmapping.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <sstream>
#include <string>
#include <stdexcept>

Mapping::PressButtonHandlerForChangeMappingUnique generatePressButtonHandlerForChangeMappingUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::PressButtonHandlerForChangeMappingUnique();

    handlerUnique = generateShiftMappingUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    //TODO
    return Mapping::PressButtonHandlerForChangeMappingUnique();
/*
    auto    oStringStream = std::ostringstream();

    const auto  KEY_TYPE = std::string( "type" );

    oStringStream << "非対応のbuttonsForChangeMappingハンドラ : " << '"' << _OBJECT.at( KEY_TYPE ).get_ref< const Json::string_t & >() << '"';

    throw std::runtime_error( oStringStream.str() );
*/
}
