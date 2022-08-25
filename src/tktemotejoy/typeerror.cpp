#include "tktemotejoy/typeerror.h"
#include "tktemotejoy/customjson.h"
#include <stdexcept>
#include <string>
#include <sstream>

std::runtime_error typeIsNotSupported(
    const Json::object_t &  _OBJECT
    , const std::string &   _HANDLERS_TYPE
)
{
    auto    oStringStream = std::ostringstream();

    const auto  KEY_TYPE = std::string( "type" );

    oStringStream << "非対応の" << _HANDLERS_TYPE << "ハンドラ : " << '"' << _OBJECT.at( KEY_TYPE ).get_ref< const Json::string_t & >() << '"';

    throw std::runtime_error( oStringStream.str() );
}
