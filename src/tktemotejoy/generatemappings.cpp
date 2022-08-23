#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"
#include <string>
#include <utility>

namespace {
    const auto  JSON = std::string( "JSON" );

    const auto  ROOT_KEY_GENERAL = std::string( "general" );
    const auto  ROOT_KEY_MAPPINGS = std::string( "mappings" );

    const auto  GENERAL_KEY_DEFAULT_MAPPING = std::string( "defaultMapping" );

    const auto  MAPPING_KEY_BUTTONS = std::string( "buttons" );

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
            throw jsonIsNotExists( ROOT_KEY_GENERAL );
        }
        const auto &    GENERAL_JSON = GENERAL_IT->second;

        if( GENERAL_JSON.is_object() == false ) {
            throw jsonIsNotObject( ROOT_KEY_GENERAL );
        }
        const auto &    GENERAL = GENERAL_JSON.get_ref< const Json::object_t & >();

        const auto  DEFAULT_MAPPING_IT = GENERAL.find( GENERAL_KEY_DEFAULT_MAPPING );
        if( DEFAULT_MAPPING_IT == GENERAL.end() ) {
            throw jsonIsNotExists(
                ROOT_KEY_GENERAL
                , GENERAL_KEY_DEFAULT_MAPPING
            );
        }
        const auto &    DEFAULT_MAPPING_JSON = DEFAULT_MAPPING_IT->second;

        if( DEFAULT_MAPPING_JSON.is_number_unsigned() == false ) {
            throw jsonIsNotUnsigned(
                ROOT_KEY_GENERAL
                , GENERAL_KEY_DEFAULT_MAPPING
            );
        }
        const auto &    DEFAULT_MAPPING = DEFAULT_MAPPING_JSON.get_ref< const Json::number_unsigned_t & >();

        return General{
            DEFAULT_MAPPING,
        };
    }

    void setButtonHandlers(
        Mapping &                   _mapping
        , const Json::object_t &    _JSON_OBJECT
    )
    {
        for( const auto & ITEM : _JSON_OBJECT ) {
            const auto  INDEX = std::stoull( ITEM.first );

            const auto &    JSON_OBJECT = ITEM.second.get_ref< const Json::object_t & >();

            auto    handlerForPspStateUnique = generatePressButtonHandlerForPspStateUnique( JSON_OBJECT );

            _mapping.setHandler(
                INDEX
                , std::move( handlerForPspStateUnique )
            );
        }
    }

    Mapping generateMapping(
        const Json::object_t &  _JSON_OBJECT
    )
    {
        auto    mapping = Mapping();

        const auto  END = _JSON_OBJECT.end();

        const auto  BUTTONS_IT = _JSON_OBJECT.find( MAPPING_KEY_BUTTONS );
        if( BUTTONS_IT != END ) {
            const auto &    BUTTONS = BUTTONS_IT->second.get_ref< const Json::object_t & >();

            setButtonHandlers(
                mapping
                , BUTTONS
            );
        }

        return mapping;
    }

    Mappings::Impl generateMappingsImpl(
        const Json::object_t &  _JSON_OBJECT
    )
    {
        const auto &    MAPPING_JSONS = _JSON_OBJECT.at( ROOT_KEY_MAPPINGS ).get_ref< const Json::array_t & >();

        auto    impl = Mappings::Impl();
        for( const auto & MAPPING_JSON : MAPPING_JSONS ) {
            const auto &    JSON_OBJECT = MAPPING_JSON.get_ref< const Json::object_t & >();

            impl.push_back( generateMapping( JSON_OBJECT ) );
        }

        return impl;
    }
}

Mappings generateMappings(
    const Json &    _JSON
)
{
    if( _JSON.is_object() == false ) {
        throw jsonIsNotObject( JSON );
    }
    const auto &    JSON_OBJECT = _JSON.get_ref< const Json::object_t & >();

    const auto  GENERAL = generateGeneral( JSON_OBJECT );

    try {
    auto    impl = generateMappingsImpl( JSON_OBJECT );

    return Mappings(
        std::move( impl )
        , GENERAL.defaultMapping
    );
    } catch( ... ) {
        return Mappings(
            Mappings::Impl()
            , GENERAL.defaultMapping
        );
    }
}
