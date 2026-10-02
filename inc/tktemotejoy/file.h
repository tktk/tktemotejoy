#ifndef TKTEMOTEJOY_FILE_H
#define TKTEMOTEJOY_FILE_H

#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>

struct GenerateStream
{
    auto operator()(
        const std::string & _FILE_NAME
    ) const
    {
        return std::ifstream( _FILE_NAME );
    }
};

template< typename GENERATE_STREAM_T = GenerateStream >
std::string readFile(
    const std::string & _FILE_NAME
)
{
    //TODO
    return std::string();
/*
    auto    stream = GENERATE_STREAM_T()( _FILE_NAME );
    if( stream.fail() == true ) {
        auto    oStringStream = std::ostringstream();

        oStringStream << "ファイル" << '"' << _FILE_NAME << '"' << "が存在しない";

        throw std::runtime_error( oStringStream.str() );
    }

    return std::string(
        std::istreambuf_iterator< char >( stream )
        , std::istreambuf_iterator< char >()
    );
*/
}

#endif  // TKTEMOTEJOY_FILE_H
