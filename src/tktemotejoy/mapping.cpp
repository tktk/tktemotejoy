#include "tktemotejoy/mapping.h"
#include "tktemotejoy/handler/forpspstate/dummy.h"
#include "tktemotejoy/handler/forchangemapping/dummy.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

namespace {
    template<
        typename HANDLERS_T
        , typename DUMMY_HANDLER_T
    >
    auto generateHandlers(
        const typename HANDLERS_T::size_type    _SIZE
    )
    {
        auto    handlers = HANDLERS_T();
        handlers.reserve( _SIZE );

        for( auto i = typename HANDLERS_T::size_type( 0 ) ; i < _SIZE ; i++ ) {
            handlers.emplace_back( new DUMMY_HANDLER_T );
        }

        return handlers;
    }

    template< typename HANDLERS_T >
    void setHandler_(
        HANDLERS_T &                                _handlers
        , const typename HANDLERS_T::size_type &    _INDEX
        , typename HANDLERS_T::value_type &&        _handlerUnique
    )
    {
        _handlers.at( _INDEX ) = std::move( _handlerUnique );
    }

    template<
        typename HANDLERS_T
        , typename CALL_HANDLER_T
    >
    auto callHandler(
        const HANDLERS_T &                      _HANDLERS
        , const typename HANDLERS_T::size_type  _INDEX
        , const CALL_HANDLER_T &                _CALL_HANDLER
    )
    {
        return _CALL_HANDLER( *( _HANDLERS.at( _INDEX ) ) );
    }

    //REMOVEME
    template<
        typename RETURNS_T
        , typename HANDLERS_T
        , typename CALL_HANDLER_T
        , typename NOT_FOUND_T
    >
    RETURNS_T callHandler_old(
        const HANDLERS_T &                      _HANDLERS
        , const typename HANDLERS_T::key_type   _KEY
        , const CALL_HANDLER_T &                _CALL_HANDLER
        , const NOT_FOUND_T &                   _NOT_FOUND
    )
    {
        const auto  IT = _HANDLERS.find( _KEY );
        if( IT == _HANDLERS.end() ) {
            return _NOT_FOUND();
        }

        return _CALL_HANDLER( *( IT->second ) );
    }

    //REMOVEME
    template<
        typename HANDLERS_T
        , typename CALL_HANDLER_T
    >
    auto callHandlerForChangeMapping_old(
        const HANDLERS_T &                      _HANDLERS
        , const typename HANDLERS_T::key_type   _KEY
        , const std::size_t                     _CURRENT_MAPPING_INDEX
        , const CALL_HANDLER_T &                _CALL_HANDLER
    )
    {
        return callHandler_old< std::size_t >(
            _HANDLERS
            , _KEY
            , _CALL_HANDLER
            , [
                &_CURRENT_MAPPING_INDEX
            ]
            {
                return _CURRENT_MAPPING_INDEX;
            }
        );
    }
}

Mapping::PressButtonHandlerForPspState::~PressButtonHandlerForPspState(
)
{
}

Mapping::OperateAxisHandlerForPspState::~OperateAxisHandlerForPspState(
)
{
}

Mapping::PressButtonHandlerForChangeMapping::~PressButtonHandlerForChangeMapping(
)
{
}

Mapping::OperateAxisHandlerForChangeMapping::~OperateAxisHandlerForChangeMapping(
)
{
}

Mapping::Mapping(
)
    : pressButtonHandlersForPspState(
        generateHandlers<
            Mapping::PressButtonHandlersForPspState
            , DummyPressButtonHandlerForPspState
        >( 100 )    //TODO
    )
    , pressButtonHandlersForChangeMapping(
        generateHandlers<
            Mapping::PressButtonHandlersForChangeMapping
            , DummyPressButtonHandlerForChangeMapping
        >( 100 )    //TODO
    )
    , operateAxisHandlersForPspState(
        generateHandlers<
            Mapping::OperateAxisHandlersForPspState
            , DummyOperateAxisHandlerForPspState
        >( 200 )    //TODO
    )
{
}

void Mapping::setHandler(
    const PressButtonHandlersForPspState::size_type _INDEX
    , PressButtonHandlersForPspState::value_type && _handlerUnique
)
{
    setHandler_(
        this->pressButtonHandlersForPspState
        , _INDEX
        , std::move( _handlerUnique )
    );
}

void Mapping::setHandler(
    const PressButtonHandlersForChangeMapping::size_type    _INDEX
    , PressButtonHandlersForChangeMapping::value_type &&    _handlerUnique
)
{
    setHandler_(
        this->pressButtonHandlersForChangeMapping
        , _INDEX
        , std::move( _handlerUnique )
    );
}

void Mapping::setHandler(
    const OperateAxisHandlersForPspState::size_type _INDEX
    , OperateAxisHandlersForPspState::value_type && _handlerUnique
)
{
    setHandler_(
        this->operateAxisHandlersForPspState
        , _INDEX
        , std::move( _handlerUnique )
    );
}

void Mapping::setHandler(
    const OperateAxisHandlersForChangeMapping::key_type     _KEY
    , OperateAxisHandlersForChangeMapping::mapped_type &&   _mappedUnique
)
{
    this->operateAxisHandlersForChangeMapping.insert(
        {
            _KEY,
            std::move( _mappedUnique ),
        }
    );
}

void Mapping::pressButton(
    const PressButtonHandlersForPspState::size_type _INDEX
    , PspState &                                    _pspState
) const
{
    callHandler(
        this->pressButtonHandlersForPspState
        , _INDEX
        , [
            &_pspState
        ]
        (
            const PressButtonHandlerForPspState &   _HANDLER
        )
        {
            _HANDLER( _pspState );
        }
    );
}

std::size_t Mapping::pressButton(
    const PressButtonHandlersForChangeMapping::size_type    _INDEX
    , std::size_t &                                         _mappingIndex
    , const std::size_t                                     _CURRENT_MAPPING_INDEX
) const
{
    return callHandler(
        this->pressButtonHandlersForChangeMapping
        , _INDEX
        , [
            &_mappingIndex
            , &_CURRENT_MAPPING_INDEX
        ]
        (
            const PressButtonHandlerForChangeMapping &  _HANDLER
        )
        {
            return _HANDLER(
                _mappingIndex
                , _CURRENT_MAPPING_INDEX
            );
        }
    );
}

void Mapping::operateAxis(
    const OperateAxisHandlersForPspState::size_type _INDEX
    , const __s16                                   _VALUE
    , PspState &                                    _pspState
) const
{
    callHandler(
        this->operateAxisHandlersForPspState
        , _INDEX
        , [
            &_VALUE
            , &_pspState
        ]
        (
            const OperateAxisHandlerForPspState &   _HANDLER
        )
        {
            _HANDLER(
                _VALUE
                , _pspState
            );
        }
    );
}

std::size_t Mapping::operateAxis(
    const OperateAxisHandlersForChangeMapping::key_type _KEY
    , const __s16                                       _VALUE
    , std::size_t &                                     _mappingIndex
    , const std::size_t                                 _CURRENT_MAPPING_INDEX
) const
{
    return callHandlerForChangeMapping_old(
        this->operateAxisHandlersForChangeMapping
        , _KEY
        , _CURRENT_MAPPING_INDEX
        , [
            &_VALUE
            , &_mappingIndex
            , &_CURRENT_MAPPING_INDEX
        ]
        (
            const OperateAxisHandlerForChangeMapping &  _HANDLER
        )
        {
            return _HANDLER(
                _VALUE
                , _mappingIndex
                , _CURRENT_MAPPING_INDEX
            );
        }
    );
}
