#include "tktemotejoy/generatehandler/operateaxishandlerforpspstate.h"
#include "tktemotejoy/generatehandler/toaxisx.h"
#include "tktemotejoy/generatehandler/toaxisy.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <sstream>
#include <string>
#include <stdexcept>

Mapping::OperateAxisHandlerForPspStateUnique generateOperateAxisHandlerForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    auto    handlerUnique = Mapping::OperateAxisHandlerForPspStateUnique();

    handlerUnique = generateToAxisXUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    handlerUnique = generateToAxisYUnique( _OBJECT );
    if( handlerUnique.get() != nullptr ) {
        return handlerUnique;
    }

    auto    oStringStream = std::ostringstream();

    const auto  KEY_TYPE = std::string( "type" );

    oStringStream << "非対応のaxes.forPspStateハンドラ : " << '"' << _OBJECT.at( KEY_TYPE ).get_ref< const Json::string_t & >() << '"';

    throw std::runtime_error( oStringStream.str() );
}
