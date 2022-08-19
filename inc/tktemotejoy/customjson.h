#ifndef TKTEMOTEJOY_CUSTOMJSON_H
#define TKTEMOTEJOY_CUSTOMJSON_H

#include "nlohmann/json.hpp"
#include <iostream>

using Json = nlohmann::json;

Json parseCustomJson(
    std::istream &
);

#endif  // TKTEMOTEJOY_CUSTOMJSON_H
