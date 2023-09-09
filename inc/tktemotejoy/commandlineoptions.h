#ifndef TKTEMOTEJOY_COMMANDLINEOPTIONS_H
#define TKTEMOTEJOY_COMMANDLINEOPTIONS_H

#include <string>

struct CommandLineOptions
{
    std::string     mapFilePath;
    std::string     deviceFilePath;
    std::string     socketName;
    unsigned char   endpoint;
};

bool initializeCommandLineOptions(
    CommandLineOptions &
    , const int
    , char * const *
);

#endif  // TKTEMOTEJOY_COMMANDLINEOPTIONS_H
