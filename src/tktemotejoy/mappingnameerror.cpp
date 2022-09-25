#include "tktemotejoy/typeerror.h"
#include <stdexcept>
#include <string>
#include <sstream>

std::runtime_error mappingNameIsNotExists(
    const std::string & _MAPPING_NAME
)
{
    auto    oStringStream = std::ostringstream();

    oStringStream << "マッピング" << '"' << _MAPPING_NAME << '"' << "が存在しない";

    return std::runtime_error( oStringStream.str() );
}
