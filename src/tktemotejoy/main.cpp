#include "tktemotejoy/commandlineoptions.h"

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

    return 0;
}
