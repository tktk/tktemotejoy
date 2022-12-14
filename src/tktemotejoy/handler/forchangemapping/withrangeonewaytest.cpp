#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/withrangeoneway.h"
#include <linux/input.h>

namespace {
    class TestHandler final
    {
        bool &              called;
        const std::size_t   RETURNS_MAPPING_INDEX;
        const __s32         EXPECTED_VALUE;
        const std::size_t & EXPECTED_MAPPING_INDEX;
        const std::size_t   EXPECTED_CURRENT_MAPPING_INDEX;

    public:
        TestHandler(
            bool &                  _called
            , const std::size_t     _RETURNS_MAPPING_INDEX
            , const __s32           _EXPECTED_VALUE
            , const std::size_t &   _EXPECTED_MAPPING_INDEX
            , const std::size_t     _EXPECTED_CURRENT_MAPPING_INDEX
        )
            : called( _called )
            , RETURNS_MAPPING_INDEX( _RETURNS_MAPPING_INDEX )
            , EXPECTED_VALUE( _EXPECTED_VALUE )
            , EXPECTED_MAPPING_INDEX( _EXPECTED_MAPPING_INDEX )
            , EXPECTED_CURRENT_MAPPING_INDEX( _EXPECTED_CURRENT_MAPPING_INDEX )
        {
        }

        std::size_t operator()(
            const __s32         _VALUE
            , std::size_t &     _mappingIndex
            , const std::size_t _CURRENT_MAPPING_INDEX
        ) const
        {
            this->called = true;

            EXPECT_EQ( this->EXPECTED_VALUE, _VALUE );
            EXPECT_EQ( &( this->EXPECTED_MAPPING_INDEX ), &_mappingIndex );
            EXPECT_EQ( this->EXPECTED_CURRENT_MAPPING_INDEX, _CURRENT_MAPPING_INDEX );

            return this->RETURNS_MAPPING_INDEX;
        }
    };

    class WithRangeOneWayForChangeMappingTest : public ::testing::Test
    {
    public:
        void test(
            const __s32         _MIN
            , const __s32       _MAX
            , const __s32       _DEAD_ZONE
            , const __s32       _VALUE
            , const std::size_t _MAPPING_INDEX
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _RETURNS_MAPPING_INDEX
            , const std::size_t _EXPECTED
            , const __s32       _EXPECTED_VALUE
            , const bool        _EXPECTED_CALLED
        ) const
        {
            auto    called = false;

            auto    mappingIndex = _MAPPING_INDEX;

            auto    withRange = WithRangeOneWayForChangeMapping(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , TestHandler(
                    called
                    , _RETURNS_MAPPING_INDEX
                    , _EXPECTED_VALUE
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            EXPECT_EQ(
                _EXPECTED
                , withRange(
                    _VALUE
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            EXPECT_EQ( _EXPECTED_CALLED, called );
        }
    };
}

TEST_F(
    WithRangeOneWayForChangeMappingTest
    , Standard
)
{
    this->test(
        -100
        , 155
        , 10
        , 92
        , 20
        , 30
        , 40
        , 40
        , 192
        , true
    );
}

TEST_F(
    WithRangeOneWayForChangeMappingTest
    , DeadZone
)
{
    this->test(
        -100
        , 155
        , 10
        , -90
        , 20
        , 30
        , 40
        , 30
        , 0
        , false
    );
}
