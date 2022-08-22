#include "tktemotejoy/file.h"
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>

std::string readFile(
    const std::string & _FILE_NAME
)
{
    auto    stream = std::ifstream( _FILE_NAME );
    if( stream.fail() == true ) {
        auto    oStringStream = std::ostringstream();

        oStringStream << "ファイル" << '"' << _FILE_NAME << '"' << "が存在しない";

        throw std::runtime_error( oStringStream.str() );
    }

    return std::string(
        std::istreambuf_iterator< char >( stream )
        , std::istreambuf_iterator< char >()
    );
}
