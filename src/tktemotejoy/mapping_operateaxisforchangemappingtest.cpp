#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>
#include <cstddef>

namespace {
    struct TestHandlerForChangeMapping final : public Mapping::OperateAxisHandlerForChangeMapping
    {
        int &               calledCount;
        const std::size_t   RETURNS_MAPPING_INDEX;
        const __s16         EXPECTED_VALUE;
        const std::size_t   EXPECTED_MAPPING_INDEX;
        const std::size_t   EXPECTED_CURRENT_MAPPING_INDEX;

        TestHandlerForChangeMapping(
            int &               _calledCount
            , const std::size_t _RETURNS_MAPPING_INDEX
            , const __s16       _EXPECTED_VALUE
            , const std::size_t _EXPECTED_MAPPING_INDEX
            , const std::size_t _EXPECTED_CURRENT_MAPPING_INDEX
        )
            : Mapping::OperateAxisHandlerForChangeMapping()
            , calledCount( _calledCount )
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
        ) const override
        {
            EXPECT_EQ( this->EXPECTED_VALUE, _VALUE );
            EXPECT_EQ( this->EXPECTED_MAPPING_INDEX, _mappingIndex );
            EXPECT_EQ( this->EXPECTED_CURRENT_MAPPING_INDEX, _CURRENT_MAPPING_INDEX );

            const_cast< int & >( this->calledCount )++;

            return this->RETURNS_MAPPING_INDEX;
        }
    };

    class Mapping_operateAxisForChangeMappingTest : public ::testing::Test
    {
    public:
        void test(
            const int           _SET_HANDLER_KEY
            , const int         _PRESS_BUTTON_KEY
            , const __s16       _VALUE
            , const std::size_t _MAPPING_INDEX
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _RETURNS_MAPPING_INDEX
            , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
            , const __s16       _EXPECTED_VALUE
            , const std::size_t _EXPECTED_MAPPING_INDEX
            , const std::size_t _EXPECTED_CURRENT_MAPPING_INDEX
            , const int         _EXPECTED_CALLED_COUNT
        ) const
        {
            auto    calledCount = 0;
            auto    mappingIndex = _MAPPING_INDEX;

            auto    handlerUnique = Mapping::HandlerUnique(
                new TestHandlerForChangeMapping(
                    calledCount
                    , _RETURNS_MAPPING_INDEX
                    , _EXPECTED_VALUE
                    , _EXPECTED_MAPPING_INDEX
                    , _EXPECTED_CURRENT_MAPPING_INDEX
                )
            );

            auto    mapping = Mapping();

            mapping.setHandler(
                _SET_HANDLER_KEY
                , std::move( handlerUnique )
            );

            EXPECT_EQ(
                _EXPECTED_NEW_MAPPING_INDEX
                , mapping.operateAxis(
                    _PRESS_BUTTON_KEY
                    , _VALUE
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            EXPECT_EQ( _EXPECTED_CALLED_COUNT, calledCount );
        }
    };
}

TEST_F(
    Mapping_operateAxisForChangeMappingTest
    , ExistsHandler
)
{
    this->test(
        10
        , 10
        , 100
        , 20
        , 30
        , 40
        , 40
        , 100
        , 20
        , 30
        , 1
    );
}

TEST_F(
    Mapping_operateAxisForChangeMappingTest
    , NotExistsHandler
)
{
    this->test(
        10
        , 20
        , 100
        , 30
        , 40
        , 50
        , 40
        , 0
        , 0
        , 0
        , 0
    );
}
