#include "tktemotejoy/typeerror.h"
#include "tktemotejoy/customjson.h"
#include <stdexcept>
#include <string>
#include <sstream>

std::runtime_error typeIsUnsupported(
    const Json::object_t &  _OBJECT
    , const std::string &   _HANDLERS_TYPE
)
{
    auto    oStringStream = std::ostringstream();

    const auto  KEY_TYPE = std::string( "type" );

    const auto  IT = _OBJECT.find( KEY_TYPE );
    if( IT != _OBJECT.end() ) {
        const auto &    TYPE_JSON = IT->second;

        oStringStream << "非対応の" << _HANDLERS_TYPE << "タイプ : " << '"' << TYPE_JSON.get_ref< const Json::string_t & >() << '"';
    } else {
        oStringStream << _HANDLERS_TYPE << "のタイプ指定がない";
    }

    throw std::runtime_error( oStringStream.str() );
}
