#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandler.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

namespace {
    class TestHandler final : public Mapping::PressButtonHandlerForChangeMapping
    {
        const std::size_t   RETURNS_OPERATOR_CALL;
        const std::size_t & EXPECTED_MAPPING_INDEX;
        const std::size_t   EXPECTED_CURRENT_MAPPING_INDEX;

    public:
        TestHandler(
            const std::size_t       _RETURNS_OPERATOR_CALL
            , const std::size_t &   _EXPECTED_MAPPING_INDEX
            , const std::size_t     _EXPECTED_CURRENT_MAPPING_INDEX
        )
            : RETURNS_OPERATOR_CALL( _RETURNS_OPERATOR_CALL )
            , EXPECTED_MAPPING_INDEX( _EXPECTED_MAPPING_INDEX )
            , EXPECTED_CURRENT_MAPPING_INDEX( _EXPECTED_CURRENT_MAPPING_INDEX )
        {
        }

        std::size_t operator()(
            std::size_t &       _mappingIndex
            , const std::size_t _CURRENT_MAPPING_INDEX
        ) const override
        {
            EXPECT_EQ( &( this->EXPECTED_MAPPING_INDEX ), &_mappingIndex );
            EXPECT_EQ( this->EXPECTED_CURRENT_MAPPING_INDEX, _CURRENT_MAPPING_INDEX );

            return this->RETURNS_OPERATOR_CALL;
        }
    };

    class ToButtonHandlerForChangeMappingTest : public ::testing::Test
    {
    public:
        void test(
            const __u16         _DEAD_ZONE
            , const __s16       _VALUE
            , const std::size_t _RETURNS_OPERATOR_CALL
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
        ) const
        {
            auto    mappingIndex = std::size_t( 10 );

            auto    handlerUnique = Mapping::PressButtonHandlerForChangeMappingUnique(
                new TestHandler(
                    _RETURNS_OPERATOR_CALL
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            auto    toButtonHandlerForChangeMapping = ToButtonHandlerForChangeMapping(
                _DEAD_ZONE
                , ToButtonHandlerForChangeMappingImpl( std::move( handlerUnique ) )
            );

            EXPECT_EQ(
                _EXPECTED_NEW_MAPPING_INDEX
                , toButtonHandlerForChangeMapping(
                    _VALUE
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );
        }
    };
}

TEST_F(
    ToButtonHandlerForChangeMappingTest
    , CallHandler
)
{
    this->test(
        50000
        , 60000 ^ 0x8000
        , 10
        , 20
        , 10
    );
}

TEST_F(
    ToButtonHandlerForChangeMappingTest
    , DeadZone
)
{
    this->test(
        50000
        , 40000 ^ 0x8000
        , 10
        , 20
        , 20
    );
}
