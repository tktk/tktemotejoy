#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/togglemapping.h"

TEST(
    ToggleMappingTest
    , OperatorCall
)
{
    auto    toggleMapping = ToggleMapping( 10 );

    auto    mappingIndex = std::size_t( 20 );

    EXPECT_EQ(
        10
        , toggleMapping( mappingIndex )
    );

    EXPECT_EQ( 10, mappingIndex );
}
