#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/generatehandler/pressbuttonhandlerforchangemapping.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforpspstate.h"
#include "tktemotejoy/generatehandler/operateaxishandlerforchangemapping.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsonerror.h"
#include "tktemotejoy/typeerror.h"
#include <cstddef>
#include <string>
#include <utility>

namespace {
    const auto  JSON = std::string( "JSON" );

    const auto  ROOT_KEY_GENERAL = std::string( "general" );
    const auto  ROOT_KEY_MAPPINGS_NEW = std::string( "mappings_new" );  //TODO mappingsにする

    const auto  GENERAL_KEY_DEFAULT_MAPPING = std::string( "defaultMapping" );

    const auto  MAPPING_KEY_BUTTONS_FOR_PSP_STATE = std::string( "buttonsForPspState" );
    const auto  MAPPING_KEY_BUTTONS_FOR_CHANGE_MAPPING = std::string( "buttonsForChangeMapping" );
    const auto  MAPPING_KEY_AXES_FOR_PSP_STATE = std::string( "axesForPspState" );
    const auto  MAPPING_KEY_AXES_FOR_CHANGE_MAPPING = std::string( "axesForChangeMapping" );

    MappingNames generateMappingNames(
        const Json::object_t &  _MAPPINGS
    )
    {
        auto    mappingNames = MappingNames();
        mappingNames.reserve( _MAPPINGS.size() );

        for( const auto & PAIR : _MAPPINGS ) {
            mappingNames.emplace_back( PAIR.first );
        }

        return mappingNames;
    }

    struct General
    {
        Mappings::Impl::size_type   defaultMapping;
    };

    General generateGeneral(
        const Json::object_t &  _OBJECT
        , const MappingNames &  _MAPPING_NAMES
    )
    {
        const auto &    GENERAL = getJsonObjectFromObject(
            _OBJECT
            , ROOT_KEY_GENERAL
        );

        const auto &    DEFAULT_MAPPING = getJsonStringFromObject(
            GENERAL
            , GENERAL_KEY_DEFAULT_MAPPING
            , ROOT_KEY_GENERAL
        );

        const auto  DEFAULT_MAPPING_INDEX = calcMappingIndex(
            _MAPPING_NAMES
            , DEFAULT_MAPPING
        );

        return General{
            DEFAULT_MAPPING_INDEX,
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
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generatePressButtonHandlerForChangeMappingUnique_new(
                _OBJECT
                , _MAPPING_NAMES
            );
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
            , const MappingNames &  _MAPPING_NAMES
        ) const
        {
            return generateOperateAxisHandlerForChangeMappingUnique_new(
                _OBJECT
                , _MAPPING_NAMES
            );
        }
    };

    template<
        typename GENERATE_HANDLER_UNIQUE_T
        , typename ... ARGS_T
    >
    void setHandlers(
        Mapping &                   _mapping
        , const Json::object_t &    _OBJECT
        , const std::string &       _KEY
        , const ARGS_T & ...        _ARGS
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

            auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()(
                MAPPING
                , _ARGS ...
            );
            if( handlerUnique.get() == nullptr ) {
                throw typeIsUnsupported(
                    MAPPING
                    , _KEY
                );
            }

            _mapping.setHandler(
                index
                , std::move( handlerUnique )
            );
        }
    }

    Mapping generateMapping(
        const Json::object_t &  _OBJECT
        , const MappingNames &  _MAPPING_NAMES
        , const std::size_t &   _BUTTONS
        , const std::size_t &   _AXES
    )
    {
        auto    mapping = Mapping(
            _BUTTONS
            , _AXES
        );

        setHandlers< GeneratePressButtonHandlerForPspStateUnique >(
            mapping
            , _OBJECT
            , MAPPING_KEY_BUTTONS_FOR_PSP_STATE
        );

        setHandlers< GeneratePressButtonHandlerForChangeMappingUnique >(
            mapping
            , _OBJECT
            , MAPPING_KEY_BUTTONS_FOR_CHANGE_MAPPING
            , _MAPPING_NAMES
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
            , _MAPPING_NAMES
        );

        return mapping;
    }

    Mappings::Impl generateMappingsImpl(
        const Json::object_t &  _MAPPINGS
        , const MappingNames &  _MAPPING_NAMES
        , const std::size_t &   _BUTTONS
        , const std::size_t &   _AXES
    )
    {
        auto    impl = Mappings::Impl();
        for( const auto & MAPPING_NAME : _MAPPING_NAMES ) {
            const auto &    MAPPING_JSON = _MAPPINGS.at( MAPPING_NAME );

            const auto &    MAPPING = getJsonObjectFromJson(
                MAPPING_JSON
                , ROOT_KEY_MAPPINGS_NEW
                , MAPPING_NAME
            );

            impl.emplace_back(
                generateMapping(
                    MAPPING
                    , _MAPPING_NAMES
                    , _BUTTONS
                    , _AXES
                )
            );
        }

        return impl;
    }
}

Mappings generateMappings(
    const Json &            _JSON
    , const std::size_t &   _BUTTONS
    , const std::size_t &   _AXES
)
{
    const auto &    OBJECT = getJsonObjectFromJson(
        _JSON
        , JSON
    );

    const auto &    MAPPINGS = getJsonObjectFromObject(
        OBJECT
        , ROOT_KEY_MAPPINGS_NEW
    );

    const auto  MAPPING_NAMES = generateMappingNames( MAPPINGS );

    const auto  GENERAL = generateGeneral(
        OBJECT
        , MAPPING_NAMES
    );

    auto    impl = generateMappingsImpl(
        MAPPINGS
        , MAPPING_NAMES
        , _BUTTONS
        , _AXES
    );

    return Mappings(
        std::move( impl )
        , GENERAL.defaultMapping
    );
}
