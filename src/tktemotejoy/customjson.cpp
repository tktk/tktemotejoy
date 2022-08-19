#include "tktemotejoy/customjson.h"
#include <string>
#include <regex>

Json parseCustomJson(
    const std::string & _STRING
)
{
    return Json::parse(
        std::regex_replace(
            _STRING
            , std::regex( R"(,(\s*(?:]|})))" )
            , "$1"
        )
    );
}
