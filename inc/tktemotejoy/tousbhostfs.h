#ifndef TKTEMOTEJOY_TOUSBHOSTFS_H
#define TKTEMOTEJOY_TOUSBHOSTFS_H

#include "tktemotejoy/descriptorcloser.h"
#include <string>

DescriptorCloser connectToUsbHostFs(
    int &
    , const std::string &
    , const unsigned short
);

bool writeToUsbHostFs(
    const int
    , const unsigned int
);

#endif  // TKTEMOTEJOY_TOUSBHOSTFS_H
