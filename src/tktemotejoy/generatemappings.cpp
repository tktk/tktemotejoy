#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemapping.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsonerror.h"
#include <cstddef>
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
        const Json::object_t &  _OBJECT
    )
    {
        const auto &    GENERAL = getJsonObjectFromObject(
            _OBJECT
            , ROOT_KEY_GENERAL
        );

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
            const Json::object_t &  _OBJECT
        ) const
        {
            return generatePressButtonHandlerForPspStateUnique( _OBJECT );
        }
    };

    struct GeneratePressButtonHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique( _OBJECT );
        }
    };

    struct GenerateOperateAxisHandlerForPspStateUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateOperateAxisHandlerForPspStateUnique( _OBJECT );
        }
    };

    struct GenerateOperateAxisHandlerForChangeMappingUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            return generateOperateAxisHandlerForChangeMappingUnique( _OBJECT );
        }
    };

    template< typename GENERATE_HANDLER_UNIQUE_T >
    void setHandlers(
        Mapping &                   _mapping
        , const Json::object_t &    _OBJECT
        , const std::string &       _KEY
    )
    {
        const auto  MAPPINGS_PTR = getJsonObjectFromObjectNotRequired(
            _OBJECT
            , _KEY
        );
        if( MAPPINGS_PTR == nullptr ) {
            return;
        }
        const auto &    MAPPINGS = *MAPPINGS_PTR;

        for( const auto & ITEM : MAPPINGS ) {
            auto    index = std::size_t( 0 );
            try {
                index = std::stoull( ITEM.first );
            } catch( ... ) {
                throw jsonObjectKeyIsNotUnsignedString(
                    _KEY
                    , ITEM.first
                );
            }

            const auto &    MAPPING_JSON = ITEM.second;
            const auto &    MAPPING = getJsonObjectFromJson(
                MAPPING_JSON
                , _KEY
                , index
            );

            auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( MAPPING );

            _mapping.setHandler(
                index
                , std::move( handlerUnique )
            );
        }
    }

    Mapping generateMapping(
        const Json::object_t &  _OBJECT
    )
    {
        auto    mapping = Mapping();

        setHandlers< GeneratePressButtonHandlerForPspStateUnique >(
            mapping
            , _OBJECT
            , MAPPING_KEY_BUTTONS_FOR_PSP_STATE
        );

        setHandlers< GeneratePressButtonHandlerForChangeMappingUnique >(
            mapping
            , _OBJECT
            , MAPPING_KEY_BUTTONS_FOR_CHANGE_MAPPING
        );

        setHandlers< GenerateOperateAxisHandlerForPspStateUnique >(
            mapping
            , _OBJECT
            , MAPPING_KEY_AXES_FOR_PSP_STATE
        );

        setHandlers< GenerateOperateAxisHandlerForChangeMappingUnique >(
            mapping
            , _OBJECT
            , MAPPING_KEY_AXES_FOR_CHANGE_MAPPING
        );

        return mapping;
    }

    Mappings::Impl generateMappingsImpl(
        const Json::object_t &  _OBJECT
    )
    {
        const auto &    MAPPINGS = getJsonArrayFromObject(
            _OBJECT
            , ROOT_KEY_MAPPINGS
        );

        auto    index = std::size_t( 0 );
        auto    impl = Mappings::Impl();
        for( const auto & MAPPING_JSON : MAPPINGS ) {
            const auto &    MAPPING = getJsonObjectFromJson(
                MAPPING_JSON
                , ROOT_KEY_MAPPINGS
                , index
            );

            impl.push_back( generateMapping( MAPPING ) );

            index++;
        }

        return impl;
    }
}

Mappings generateMappings(
    const Json &    _JSON
)
{
    const auto &    OBJECT = getJsonObjectFromJson(
        _JSON
        , JSON
    );

    const auto  GENERAL = generateGeneral( OBJECT );

    auto    impl = generateMappingsImpl( OBJECT );

    return Mappings(
        std::move( impl )
        , GENERAL.defaultMapping
    );
}
