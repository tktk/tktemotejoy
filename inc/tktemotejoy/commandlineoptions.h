#ifndef TKTEMOTEJOY_COMMANDLINEOPTIONS_H
#define TKTEMOTEJOY_COMMANDLINEOPTIONS_H

#include <string>

struct CommandLineOptions
{
    std::string     mapFilePath;
    std::string     deviceFilePath;
    std::string     ip;
    unsigned short  port;
};

bool initializeCommandLineOptions(
    CommandLineOptions &
    , const int
    , char * const *
);

#endif  // TKTEMOTEJOY_COMMANDLINEOPTIONS_H
