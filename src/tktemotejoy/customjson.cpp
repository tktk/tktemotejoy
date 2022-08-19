#include "tktemotejoy/customjson.h"
#include <string>
#include <regex>

Json parseCustomJson(
    const std::string & _STRING
)
{
    const auto  REMOVE_LINE_COMMENT = std::regex_replace(
        _STRING
        , std::regex( R"(\s*//.*)" )
        , ""
    );

    const auto  REMOVE_BLOCK_COMMENT = std::regex_replace(
        REMOVE_LINE_COMMENT
        , std::regex( R"(/\*(?:.|\s)*\*/)" )
        , ""
    );

    const auto  REMOVE_TAIL_COMMA = std::regex_replace(
        REMOVE_BLOCK_COMMENT
        , std::regex( R"(,(\s*[\]\}]))" )
        , "$1"
    );

    return Json::parse( REMOVE_TAIL_COMMA );
}
