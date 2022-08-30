#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/withdeadzoneunsigned.h"
#include <linux/joystick.h>
#include <cstddef>

namespace {
    class TestHandler final
    {
        bool &              called;
        const std::size_t   RETURNS_MAPPING_INDEX;
        const __u16         EXPECTED_VALUE;
        const std::size_t & EXPECTED_MAPPING_INDEX;
        const std::size_t   EXPECTED_CURRENT_MAPPING_INDEX;

    public:
        TestHandler(
            bool &                  _called
            , const std::size_t     _RETURNS_MAPPING_INDEX
            , const __u16           _EXPECTED_VALUE
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
            const __u16         _VALUE
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

    class WithDeadZoneUnsignedForChangeMappingTest : public ::testing::Test
    {
    public:
        void test(
            const __u16         _DEAD_ZONE
            , const __s16       _VALUE
            , const std::size_t _MAPPING_INDEX
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _RETURNS_MAPPING_INDEX
            , const __u16       _EXPECTED_VALUE
            , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
            , const bool        _EXPECTED_CALLED
        ) const
        {
            auto    called = false;
            auto    mappingIndex = _MAPPING_INDEX;

            auto    withDeadZone = WithDeadZoneUnsignedForChangeMapping(
                _DEAD_ZONE
                , TestHandler(
                    called
                    , _RETURNS_MAPPING_INDEX
                    , _EXPECTED_VALUE
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            EXPECT_EQ(
                _EXPECTED_NEW_MAPPING_INDEX
                , withDeadZone(
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
    WithDeadZoneUnsignedForChangeMappingTest
    , OutOfDeadZone
)
{
    this->test(
        50000
        , 60000 ^ 0x8000
        , 10
        , 20
        , 30
        , 60000
        , 30
        , true
    );
}

TEST_F(
    WithDeadZoneUnsignedForChangeMappingTest
    , DeadZone
)
{
    this->test(
        50000
        , 40000 ^ 0x8000
        , 10
        , 20
        , 30
        , 40000
        , 20
        , false
    );
}
