#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <utility>

namespace {
    void callHandlerForPspState(
        const Mapping::HandlersForPspState &            _HANDLERS
        , const Mapping::HandlersForPspState::key_type  _KEY
        , const __s16                                   _VALUE
        , PspState &                                    _pspState
    )
    {
        const auto  IT = _HANDLERS.find( _KEY );
        if( IT == _HANDLERS.end() ) {
            return;
        }

        ( *( IT->second ) )(
            _VALUE
            , _pspState
        );
    }

    std::size_t callHandlerForChangeMapping(
        const Mapping::HandlersForChangeMapping &           _HANDLERS
        , const Mapping::HandlersForChangeMapping::key_type _KEY
        , const __s16                                       _VALUE
        , std::size_t &                                     _mappingIndex
        , const std::size_t                                 _CURRENT_MAPPING_INDEX
    )
    {
        const auto  IT = _HANDLERS.find( _KEY );
        if( IT == _HANDLERS.end() ) {
            return _CURRENT_MAPPING_INDEX;
        }

        return ( *( IT->second ) )(
            _VALUE
            , _mappingIndex
        );
    }
}

Mapping::HandlerForPspState::~HandlerForPspState(
)
{
}

Mapping::HandlerForChangeMapping::~HandlerForChangeMapping(
)
{
}

void Mapping::setPressButtonHandler(
    const HandlersForPspState::key_type     _KEY
    , HandlersForPspState::mapped_type &&   _mappedUnique
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
    const HandlersForChangeMapping::key_type    _KEY
    , HandlersForChangeMapping::mapped_type &&  _mappedUnique
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
    const HandlersForPspState::key_type     _KEY
    , HandlersForPspState::mapped_type &&   _mappedUnique
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
    const HandlersForChangeMapping::key_type    _KEY
    , HandlersForChangeMapping::mapped_type &&  _mappedUnique
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
    const HandlersForPspState::key_type _KEY
    , PspState &                        _pspState
) const
{
    callHandlerForPspState(
        this->pressButtonHandlersForPspState
        , _KEY
        , 1
        , _pspState
    );
}

std::size_t Mapping::pressButton(
    const HandlersForChangeMapping::key_type    _KEY
    , std::size_t &                             _mappingIndex
    , const std::size_t                         _CURRENT_MAPPING_INDEX
) const
{
    return callHandlerForChangeMapping(
        this->pressButtonHandlersForChangeMapping
        , _KEY
        , 1
        , _mappingIndex
        , _CURRENT_MAPPING_INDEX
    );
}

void Mapping::operateAxis(
    const HandlersForPspState::key_type _KEY
    , const __s16                       _VALUE
    , PspState &                        _pspState
) const
{
    callHandlerForPspState(
        this->operateAxisHandlersForPspState
        , _KEY
        , _VALUE
        , _pspState
    );
}

std::size_t Mapping::operateAxis(
    const HandlersForChangeMapping::key_type    _KEY
    , const __s16                               _VALUE
    , std::size_t &                             _mappingIndex
    , const std::size_t                         _CURRENT_MAPPING_INDEX
) const
{
    return callHandlerForChangeMapping(
        this->operateAxisHandlersForChangeMapping
        , _KEY
        , _VALUE
        , _mappingIndex
        , _CURRENT_MAPPING_INDEX
    );
}
