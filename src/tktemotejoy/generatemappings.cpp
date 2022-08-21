#include "tktemotejoy/generatemappings.h"
#include "tktemotejoy/mappings.h"
#include "tktemotejoy/customjson.h"
#include <utility>

Mappings generateMappings(
    const Json &    _JSON
)
{
    //TODO
    auto    impl = Mappings::Impl();
    impl.push_back( Mapping() );

    return Mappings(
        std::move( impl )
        , 0
    );
}
