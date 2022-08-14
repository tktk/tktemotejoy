#include "tktemotejoy/mapping.h"
#include <utility>

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

//TODO 要リファクタリング
void Mapping::pressButton(
    const HandlersForPspState::key_type _KEY
    , PspState &                        _pspState
) const
{
    const auto  IT = this->pressButtonHandlersForPspState.find( _KEY );
    if( IT == this->pressButtonHandlersForPspState.end() ) {
        return;
    }

    ( *( IT->second ) )(
        1
        , _pspState
    );
}

std::size_t Mapping::pressButton(
    const HandlersForChangeMapping::key_type
    , std::size_t &
    , const std::size_t
) const
{
    //TODO
    return false;
}

//TODO 要リファクタリング
void Mapping::operateAxis(
    const HandlersForPspState::key_type _KEY
    , const __s16                       _VALUE
    , PspState &                        _pspState
) const
{
    const auto  IT = this->operateAxisHandlersForPspState.find( _KEY );
    if( IT == this->operateAxisHandlersForPspState.end() ) {
        return;
    }

    ( *( IT->second ) )(
        _VALUE
        , _pspState
    );
}

std::size_t Mapping::operateAxis(
    const HandlersForChangeMapping::key_type
    , const __s16
    , std::size_t &
    , const std::size_t
) const
{
    //TODO
    return false;
}
