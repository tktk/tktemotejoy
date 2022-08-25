#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemapping.h"
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

    const auto  MAPPING_KEY_BUTTONS_FOR_PSP_STATE = std::string( "buttonsForPspState" );
    const auto  MAPPING_KEY_BUTTONS_FOR_CHANGE_MAPPING = std::string( "buttonsForChangeMapping" );
    const auto  MAPPING_KEY_AXES_FOR_PSP_STATE = std::string( "axesForPspState" );
    const auto  MAPPING_KEY_AXES_FOR_CHANGE_MAPPING = std::string( "axesForChangeMapping" );

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

    struct GeneratePressButtonHandlerForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _JSON_OBJECT
        ) const
        {
            return generatePressButtonHandlerForPspStateUnique( _JSON_OBJECT );
        }
    };

    struct GeneratePressButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _JSON_OBJECT
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique( _JSON_OBJECT );
        }
    };

    struct GenerateOperateAxisHandlerForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _JSON_OBJECT
        ) const
        {
            return generateOperateAxisHandlerForPspStateUnique( _JSON_OBJECT );
        }
    };

    struct GenerateOperateAxisHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _JSON_OBJECT
        ) const
        {
            return generateOperateAxisHandlerForChangeMappingUnique( _JSON_OBJECT );
        }
    };

    template< typename GENERATE_HANDLER_UNIQUE_T >
    void setHandlers(
        Mapping &                   _mapping
        , const Json::object_t &    _JSON_OBJECT
        , const std::string &       _KEY
    )
    {
        const auto  IT = _JSON_OBJECT.find( _KEY );
        if( IT == _JSON_OBJECT.end() ) {
            return;
        }

        const auto &    MAPPINGS_JSON = IT->second;
        const auto &    MAPPINGS = MAPPINGS_JSON.get_ref< const Json::object_t & >();

        for( const auto & ITEM : MAPPINGS ) {
            const auto  INDEX = std::stoull( ITEM.first );

            const auto &    MAPPING_JSON = ITEM.second;
            const auto &    MAPPING = MAPPING_JSON.get_ref< const Json::object_t & >();

            auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( MAPPING );

            _mapping.setHandler(
                INDEX
                , std::move( handlerUnique )
            );
        }
    }

    Mapping generateMapping(
        const Json::object_t &  _JSON_OBJECT
    )
    {
        auto    mapping = Mapping();

        setHandlers< GeneratePressButtonHandlerForPspStateUnique >(
            mapping
            , _JSON_OBJECT
            , MAPPING_KEY_BUTTONS_FOR_PSP_STATE
        );

        setHandlers< GeneratePressButtonHandlerForChangeMappingUnique >(
            mapping
            , _JSON_OBJECT
            , MAPPING_KEY_BUTTONS_FOR_CHANGE_MAPPING
        );

        setHandlers< GenerateOperateAxisHandlerForPspStateUnique >(
            mapping
            , _JSON_OBJECT
            , MAPPING_KEY_AXES_FOR_PSP_STATE
        );

        setHandlers< GenerateOperateAxisHandlerForChangeMappingUnique >(
            mapping
            , _JSON_OBJECT
            , MAPPING_KEY_AXES_FOR_CHANGE_MAPPING
        );

        return mapping;
    }

    Mappings::Impl generateMappingsImpl(
        const Json::object_t &  _JSON_OBJECT
    )
    {
        const auto  IT = _JSON_OBJECT.find( ROOT_KEY_MAPPINGS );
        if( IT == _JSON_OBJECT.end() ) {
            throw jsonIsNotExists( ROOT_KEY_MAPPINGS );
        }
        const auto &    MAPPINGS_JSON = IT->second;

        const auto &    MAPPING_JSONS = MAPPINGS_JSON.get_ref< const Json::array_t & >();   //TODO 要エラーチェック

        auto    impl = Mappings::Impl();
        for( const auto & MAPPING_JSON : MAPPING_JSONS ) {
            const auto &    JSON_OBJECT = MAPPING_JSON.get_ref< const Json::object_t & >(); //TODO 要エラーチェック

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

    auto    impl = generateMappingsImpl( JSON_OBJECT );

    return Mappings(
        std::move( impl )
        , GENERAL.defaultMapping
    );
}
