#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forchangemapping/tochangemappinghandlers.h"
#include "tktemotejoy/mapping.h"
#include <linux/joystick.h>
#include <cstddef>
#include <utility>

namespace {
    class TestHandler final : public Mapping::PressButtonHandlerForChangeMapping
    {
        const std::size_t   RETURNS_OPERATOR_CALL;
        const std::size_t & EXPECTED_MAPPING_INDEX;

    public:
        TestHandler(
            const std::size_t       _RETURNS_OPERATOR_CALL
            , const std::size_t &   _EXPECTED_MAPPING_INDEX
        )
            : RETURNS_OPERATOR_CALL( _RETURNS_OPERATOR_CALL )
            , EXPECTED_MAPPING_INDEX( _EXPECTED_MAPPING_INDEX )
        {
        }

        std::size_t operator()(
            std::size_t &       _mappingIndex
            , const std::size_t _CURRENT_MAPPING_INDEX  //TODO
        ) const override
        {
            EXPECT_EQ( &( this->EXPECTED_MAPPING_INDEX ), &_mappingIndex );

            return this->RETURNS_OPERATOR_CALL;
        }
    };

    class ToChangeMappingHandlersTest : public ::testing::Test
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
                )
            );
            auto    handler2Unique = Mapping::PressButtonHandlerForChangeMappingUnique(
                new TestHandler(
                    _RETURNS_OPERATOR_CALL2
                    , mappingIndex
                )
            );

            auto    toChangeMappingHandlers = ToChangeMappingHandlers(
                _DEAD_ZONE
                , ToChangeMappingHandlersImpl(
                    std::move( handler1Unique )
                    , std::move( handler2Unique )
                )
            );

            EXPECT_EQ(
                _EXPECTED_NEW_MAPPING_INDEX
                , toChangeMappingHandlers(
                    _VALUE
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );
        }
    };
}

TEST_F(
    ToChangeMappingHandlersTest
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
    ToChangeMappingHandlersTest
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
    ToChangeMappingHandlersTest
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
