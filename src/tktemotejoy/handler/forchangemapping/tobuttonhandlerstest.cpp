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

    //FIXME
    class ToButtonHandlersForChangeMapping_newTest : public ::testing::Test
    {
    public:
        void test(
            const __s16         _MIN
            , const __s16       _MAX
            , const __s16       _DEAD_ZONE
            , const __s16       _VALUE
            , const std::size_t _RETURNS_OPERATOR_CALL_MINUS
            , const std::size_t _RETURNS_OPERATOR_CALL_PLUS
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
        ) const
        {
            auto    mappingIndex = std::size_t( 10 );

            auto    handlerMinusUnique = Mapping::PressButtonHandlerForChangeMappingUnique(
                new TestHandler(
                    _RETURNS_OPERATOR_CALL_MINUS
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );
            auto    handlerPlusUnique = Mapping::PressButtonHandlerForChangeMappingUnique(
                new TestHandler(
                    _RETURNS_OPERATOR_CALL_PLUS
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            auto    toButtonHandlersForChangeMapping = ToButtonHandlersForChangeMapping_new(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToButtonHandlersForChangeMapping_newImpl(
                    std::move( handlerMinusUnique )
                    , std::move( handlerPlusUnique )
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
    ToButtonHandlersForChangeMapping_newTest
    , CallHandlerMinus
)
{
    this->test(
        0
        , 255
        , 10
        , 117
        , 10
        , 20
        , 30
        , 10
    );
}

TEST_F(
    ToButtonHandlersForChangeMapping_newTest
    , CallHandlerPlus
)
{
    this->test(
        0
        , 255
        , 10
        , 139
        , 10
        , 20
        , 30
        , 20
    );
}

TEST_F(
    ToButtonHandlersForChangeMapping_newTest
    , DeadZone
)
{
    this->test(
        0
        , 255
        , 10
        , 138
        , 10
        , 20
        , 30
        , 30
    );
}
