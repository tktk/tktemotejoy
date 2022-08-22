#include "tktemotejoy/commandlineoptions.h"
#include "tktemotejoy/file.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include <string>

namespace {
    Mappings generateMappingsFromFile(
        const std::string & _FILE_PATH
    )
    {
        const auto  JSON_STRING = readFile( _FILE_PATH );

        const auto  JSON = parseCustomJson( JSON_STRING );

        return generateMappings( JSON );
    }
}

int main(
    const int       _ARGC
    , const char ** _ARGV
)
{
    auto    options = CommandLineOptions();
    if( initializeCommandLineOptions(
        options
        , _ARGC
        , _ARGV
    ) == false ) {
        return 1;
    }

    auto    mappings = generateMappingsFromFile( options.mapFilePath );

    return 0;
}
