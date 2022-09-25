#include "tktemotejoy/mappingnames.h"
#include "tktemotejoy/mappingnameerror.h"
#include <algorithm>
#include <iterator>

MappingNames::size_type calcMappingIndex(
    const MappingNames &                _MAPPING_NAMES
    , const MappingNames::value_type &  _MAPPING_NAME
)
{
    const auto  MAPPING_NAMES_BEGIN = _MAPPING_NAMES.begin();
    const auto  MAPPING_NAMES_END = _MAPPING_NAMES.end();

    const auto  IT = std::lower_bound(
        MAPPING_NAMES_BEGIN
        , MAPPING_NAMES_END
        , _MAPPING_NAME
    );
    if( IT == MAPPING_NAMES_END ) {
        throw mappingNameIsNotExists( _MAPPING_NAME );
    }

    const auto  MAPPING_INDEX = std::distance(
        MAPPING_NAMES_BEGIN
        , IT
    );

    return MappingNames::size_type( MAPPING_INDEX );
}
