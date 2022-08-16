#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <utility>

namespace {
    template<
        typename RETURNS_T
        , typename HANDLERS_T
        , typename CALL_HANDLER_T
        , typename NOT_FOUND_T
    >
    RETURNS_T callHandler(
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

    template<
        typename HANDLERS_T
        , typename CALL_HANDLER_T
    >
    auto callHandlerForPspState(
        const HANDLERS_T &                      _HANDLERS
        , const typename HANDLERS_T::key_type   _KEY
        , const CALL_HANDLER_T &                _CALL_HANDLER
    )
    {
        return callHandler< void >(
            _HANDLERS
            , _KEY
            , _CALL_HANDLER
            , []{}
        );
    }

    template<
        typename HANDLERS_T
        , typename CALL_HANDLER_T
    >
    auto callHandlerForChangeMapping(
        const HANDLERS_T &                      _HANDLERS
        , const typename HANDLERS_T::key_type   _KEY
        , const std::size_t                     _CURRENT_MAPPING_INDEX
        , const CALL_HANDLER_T &                _CALL_HANDLER
    )
    {
        return callHandler< std::size_t >(
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

void Mapping::setPressButtonHandler(
    const PressButtonHandlersForPspState::key_type      _KEY
    , PressButtonHandlersForPspState::mapped_type &&    _mappedUnique
)
{
    this->pressButtonHandlersForPspState.insert(
        {
            _KEY,
            std::move( _mappedUnique ),
        }
    );
}

void Mapping::setPressButtonHandler(
    const PressButtonHandlersForChangeMapping::key_type     _KEY
    , PressButtonHandlersForChangeMapping::mapped_type &&   _mappedUnique
)
{
    this->pressButtonHandlersForChangeMapping.insert(
        {
            _KEY,
            std::move( _mappedUnique ),
        }
    );
}

void Mapping::setOperateAxisHandler(
    const OperateAxisHandlersForPspState::key_type      _KEY
    , OperateAxisHandlersForPspState::mapped_type &&    _mappedUnique
)
{
    this->operateAxisHandlersForPspState.insert(
        {
            _KEY,
            std::move( _mappedUnique ),
        }
    );
}

void Mapping::setOperateAxisHandler(
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
    const PressButtonHandlersForPspState::key_type  _KEY
    , PspState &                                    _pspState
) const
{
    callHandlerForPspState(
        this->pressButtonHandlersForPspState
        , _KEY
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
    const PressButtonHandlersForChangeMapping::key_type _KEY
    , std::size_t &                                     _mappingIndex
    , const std::size_t                                 _CURRENT_MAPPING_INDEX
) const
{
    return callHandlerForChangeMapping(
        this->pressButtonHandlersForChangeMapping
        , _KEY
        , _CURRENT_MAPPING_INDEX
        , [
            &_mappingIndex
        ]
        (
            const PressButtonHandlerForChangeMapping &  _HANDLER
        )
        {
            return _HANDLER( _mappingIndex );
        }
    );
}

void Mapping::operateAxis(
    const OperateAxisHandlersForPspState::key_type  _KEY
    , const __s16                                   _VALUE
    , PspState &                                    _pspState
) const
{
    callHandlerForPspState(
        this->operateAxisHandlersForPspState
        , _KEY
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
    return callHandlerForChangeMapping(
        this->operateAxisHandlersForChangeMapping
        , _KEY
        , _CURRENT_MAPPING_INDEX
        , [
            &_VALUE
            , &_mappingIndex
        ]
        (
            const OperateAxisHandlerForChangeMapping &  _HANDLER
        )
        {
            return _HANDLER(
                _VALUE
                , _mappingIndex
            );
        }
    );
}
