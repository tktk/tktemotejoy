#include "tktemotejoy/customjson.h"
#include <iostream>

Json parseCustomJson(
    std::istream &  _iStream
)
{
    return Json::parse( _iStream );
}
