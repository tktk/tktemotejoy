#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/tobuttonhandlers.h"
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

    class ToButtonHandlersForChangeMappingTest : public ::testing::Test
    {
    public:
        void test(
            const __s16         _DEAD_ZONE
            , const __s16       _VALUE
            , const std::size_t _RETURNS_OPERATOR_CALL1
            , const std::size_t _RETURNS_OPERATOR_CALL2
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
        ) const
        {
            auto    mappingIndex = std::size_t( 10 );

            auto    handler1Unique = Mapping::PressButtonHandlerForChangeMappingUnique(
                new TestHandler(
                    _RETURNS_OPERATOR_CALL1
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );
            auto    handler2Unique = Mapping::PressButtonHandlerForChangeMappingUnique(
                new TestHandler(
                    _RETURNS_OPERATOR_CALL2
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            auto    toButtonHandlersForChangeMapping = ToButtonHandlersForChangeMapping(
                _DEAD_ZONE
                , ToButtonHandlersForChangeMappingImpl(
                    std::move( handler1Unique )
                    , std::move( handler2Unique )
                )
            );

            EXPECT_EQ(
                _EXPECTED_NEW_MAPPING_INDEX
                , toButtonHandlersForChangeMapping(
                    _VALUE
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );
        }
    };
}

TEST_F(
    ToButtonHandlersForChangeMappingTest
    , CallHandler1
)
{
    this->test(
        0
        , -1
        , 10
        , 20
        , 30
        , 10
    );
}

TEST_F(
    ToButtonHandlersForChangeMappingTest
    , CallHandler2
)
{
    this->test(
        0
        , 1
        , 10
        , 20
        , 30
        , 20
    );
}

TEST_F(
    ToButtonHandlersForChangeMappingTest
    , DeadZone
)
{
    this->test(
        0
        , 0
        , 10
        , 20
        , 30
        , 30
    );
}
