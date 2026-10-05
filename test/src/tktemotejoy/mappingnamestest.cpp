#include "tktemotejoy/test.h"
#include "tktemotejoy/mappingnames.h"
#include <string>

namespace {
    class CalcMappingIndexTest : public ::testing::Test
    {
    public:
        void test(
            const tktemotejoy::MappingNames &               _MAPPING_NAMES
            , const std::string &                           _MAPPING_NAME
            , const tktemotejoy::MappingNames::size_type    _EXPECTED
        ) const
        {
            EXPECT_EQ(
                _EXPECTED
                , tktemotejoy::calcMappingIndex(
                    _MAPPING_NAMES
                    , _MAPPING_NAME
                )
            );
        }

        void testAnyThrow(
            const tktemotejoy::MappingNames &   _MAPPING_NAMES
            , const std::string &               _MAPPING_NAME
        ) const
        {
            EXPECT_ANY_THROW(
                tktemotejoy::calcMappingIndex(
                    _MAPPING_NAMES
                    , _MAPPING_NAME
                )
            );
        }
    };
}

TEST_F(
    CalcMappingIndexTest
    , Standard
)
{
    this->test(
        {
            "mapping1",
            "mapping2",
            "mapping3",
            "mapping4",
            "mapping5",
        }
        , "mapping3"
        , 2
    );
}

TEST_F(
    CalcMappingIndexTest
    , FailedNotExists
)
{
    this->testAnyThrow(
        {
            "mapping1",
            "mapping2",
            "mapping3",
            "mapping4",
            "mapping5",
        }
        , "notExists"
    );
}
