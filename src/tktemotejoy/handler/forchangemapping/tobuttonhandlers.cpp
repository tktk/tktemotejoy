#include "tktemotejoy/handler/forchangemapping/tobuttonhandlers.h"
#include "tktemotejoy/mapping.h"
#include <linux/input.h>
#include <cstddef>
#include <utility>

ToButtonHandlersForChangeMappingImpl::ToButtonHandlersForChangeMappingImpl(
    Mapping::PressButtonHandlerForChangeMappingUnique &&    _handlerMinusUnique
    , Mapping::PressButtonHandlerForChangeMappingUnique &&  _handlerPlusUnique
)
    : handlerMinusUnique( std::move( _handlerMinusUnique ) )
    , handlerPlusUnique( std::move( _handlerPlusUnique ) )
{
}

std::size_t ToButtonHandlersForChangeMappingImpl::operator()(
    const __s32         _VALUE
    , std::size_t &     _mappingIndex
    , const std::size_t _CURRENT_MAPPING_INDEX
) const
{
    const auto &    HANDLER = *( _VALUE < 0 ? this->handlerMinusUnique : this->handlerPlusUnique );

    return HANDLER(
        _mappingIndex
        , _CURRENT_MAPPING_INDEX
    );
}
