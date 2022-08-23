#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/dummy.h"

TEST(
    DummyPressButtonHandlerForChangeMappingTest
    , OperatorCall
)
{
    auto    dummy = DummyPressButtonHandlerForChangeMapping();

    auto    mappingIndex = std::size_t( 10 );

    EXPECT_EQ(
        10
        , dummy( mappingIndex )
    );

    EXPECT_EQ( 10, mappingIndex );
}
