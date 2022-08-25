#ifndef TKTEMOTEJOY_TYPEERROR_H
#define TKTEMOTEJOY_TYPEERROR_H

#include "tktemotejoy/customjson.h"
#include <stdexcept>
#include <string>

std::runtime_error typeIsNotSupported(
    const Json::object_t &
    , const std::string &
);

#endif  // TKTEMOTEJOY_TYPEERROR_H
