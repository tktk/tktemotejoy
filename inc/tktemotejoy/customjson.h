#ifndef TKTEMOTEJOY_CUSTOMJSON_H
#define TKTEMOTEJOY_CUSTOMJSON_H

#include "nlohmann/json.hpp"
#include <string>

using Json = nlohmann::json;

Json parseCustomJson(
    const std::string &
);

#endif  // TKTEMOTEJOY_CUSTOMJSON_H
