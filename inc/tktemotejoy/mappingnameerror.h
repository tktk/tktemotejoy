#ifndef TKTEMOTEJOY_MAPPINGNAMEERROR_H
#define TKTEMOTEJOY_MAPPINGNAMEERROR_H

#include <stdexcept>
#include <string>

namespace tktemotejoy {
    std::runtime_error mappingNameIsNotExists(
        const std::string &
    );
}

#endif  // TKTEMOTEJOY_MAPPINGNAMEERROR_H
