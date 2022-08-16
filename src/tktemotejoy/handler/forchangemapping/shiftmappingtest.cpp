#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/shiftmapping.h"

TEST(
    ShiftMappingTest
    , OperatorCall
)
{
    auto    shiftMapping = ShiftMapping( 10 );

    auto        mappingIndex = std::size_t( 20 );
    const auto  CURRENT_MAPPING_INDEX = std::size_t( 20 );

    EXPECT_EQ(
        10
        , shiftMapping(
            40
            , mappingIndex
            , CURRENT_MAPPING_INDEX
        )
    );

    EXPECT_EQ( 20, mappingIndex );
}
