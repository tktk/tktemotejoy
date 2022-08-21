#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <utility>
#include <sstream>
#include <stdexcept>

namespace {
    const auto  ROOT_KEY_GENERAL = std::string( "general" );
    const auto  ROOT_KEY_MAPPINGS = std::string( "mappings" );

    const auto  GENERAL_KEY_DEFAULT_MAPPING = std::string( "defaultMapping" );

    struct General
    {
        Mappings::Impl::size_type   defaultMapping;
    };

    General generateGeneral(
        const Json::object_t &  _JSON_OBJECT
    )
    {
        const auto  GENERAL_IT = _JSON_OBJECT.find( ROOT_KEY_GENERAL );
        if( GENERAL_IT == _JSON_OBJECT.end() ) {
            auto    oStringStream = std::ostringstream();

            oStringStream << '"' << ROOT_KEY_GENERAL << '"' << "が存在しない";

            throw std::runtime_error( oStringStream.str() );
        }
        const auto &    GENERAL_JSON = GENERAL_IT->second;

        if( GENERAL_JSON.is_object() == false ) {
            auto    oStringStream = std::ostringstream();

            oStringStream << '"' << ROOT_KEY_GENERAL << '"' << "がオブジェクトではない";

            throw std::runtime_error( oStringStream.str() );
        }
        const auto &    GENERAL = GENERAL_JSON.get_ref< const Json::object_t & >();

        const auto &    DEFAULT_MAPPING = GENERAL.at( GENERAL_KEY_DEFAULT_MAPPING ).get_ref< const Json::number_unsigned_t & >();

        return General{
            DEFAULT_MAPPING,
        };
    }

    Mappings::Impl generateMappingsImpl(
        const Json::object_t &  _JSON_OBJECT
    )
    {
        //TODO
        auto    impl = Mappings::Impl();
        impl.push_back( Mapping() );

        return impl;
    }
}

Mappings generateMappings(
    const Json &    _JSON
)
{
    const auto &    JSON_OBJECT = _JSON.get_ref< const Json::object_t & >();

    const auto  GENERAL = generateGeneral( JSON_OBJECT );

    auto    impl = generateMappingsImpl( JSON_OBJECT );

    return Mappings(
        std::move( impl )
        , GENERAL.defaultMapping
    );
}
