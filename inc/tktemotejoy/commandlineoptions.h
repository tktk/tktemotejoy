#ifndef TKTEMOTEJOY_COMMANDLINEOPTIONS_H
#define TKTEMOTEJOY_COMMANDLINEOPTIONS_H

#include <string>

struct CommandLineOptions
{
    std::string     mapFilePath;
    std::string     ip;
    unsigned short  port;
    std::string     deviceFilePath;
};

bool initializeCommandLineOptions(
    CommandLineOptions &
    , const int
    , const char **
);

#endif  // TKTEMOTEJOY_COMMANDLINEOPTIONS_H
