#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/withdeadzone.h"
#include <linux/joystick.h>
#include <cstddef>

namespace {
    class TestHandler final
    {
        bool &              called;
        const std::size_t   RETURNS_MAPPING_INDEX;
        const __s16         EXPECTED_VALUE;
        const std::size_t & EXPECTED_MAPPING_INDEX;
        const std::size_t   EXPECTED_CURRENT_MAPPING_INDEX;

    public:
        TestHandler(
            bool &                  _called
            , const std::size_t     _RETURNS_MAPPING_INDEX
            , const __s16           _EXPECTED_VALUE
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
            const __s16         _VALUE
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

    class WithDeadZoneForChangeMappingTest : public ::testing::Test
    {
    public:
        void test(
            const __s16         _DEAD_ZONE
            , const __s16       _VALUE
            , const std::size_t _MAPPING_INDEX
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _RETURNS_MAPPING_INDEX
            , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
            , const bool        _EXPECTED_CALLED
        ) const
        {
            auto    called = false;
            auto    mappingIndex = _MAPPING_INDEX;

            auto    withDeadZone = WithDeadZoneForChangeMapping(
                _DEAD_ZONE
                , TestHandler(
                    called
                    , _RETURNS_MAPPING_INDEX
                    , _VALUE
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
    WithDeadZoneForChangeMappingTest
    , OutOfDeadZonePlus
)
{
    this->test(
        0
        , 2000
        , 10
        , 20
        , 30
        , 30
        , true
    );
}

//TODO
/*
TEST_F(
    WithDeadZoneForChangeMappingTest
    , OutOfDeadZoneMinus
)
{
    this->test(
        0
        , -2000
        , 10
        , 20
        , 30
        , 30
        , true
    );
}
*/

TEST_F(
    WithDeadZoneForChangeMappingTest
    , DeadZonePlus
)
{
    this->test(
        1000
        , 1000
        , 10
        , 20
        , 30
        , 20
        , false
    );
}

TEST_F(
    WithDeadZoneForChangeMappingTest
    , DeadZoneMinus
)
{
    this->test(
        1000
        , -1000
        , 10
        , 20
        , 30
        , 20
        , false
    );
}
