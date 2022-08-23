#include "tktemotejoy/test.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>
#include <cstddef>

namespace {
    class TestHandlerForChangeMapping final : public Mapping::PressButtonHandlerForChangeMapping
    {
        int &               calledCount;
        const std::size_t   RETURNS_MAPPING_INDEX;
        const std::size_t   EXPECTED_MAPPING_INDEX;

    public:
        TestHandlerForChangeMapping(
            int &               _calledCount
            , const std::size_t _RETURNS_MAPPING_INDEX
            , const std::size_t _EXPECTED_MAPPING_INDEX
        )
            : Mapping::PressButtonHandlerForChangeMapping()
            , calledCount( _calledCount )
            , RETURNS_MAPPING_INDEX( _RETURNS_MAPPING_INDEX )
            , EXPECTED_MAPPING_INDEX( _EXPECTED_MAPPING_INDEX )
        {
        }

        std::size_t operator()(
            std::size_t &       _mappingIndex
            , const std::size_t _CURRENT_MAPPING_INDEX  //TODO
        ) const override
        {
            EXPECT_EQ( this->EXPECTED_MAPPING_INDEX, _mappingIndex );

            const_cast< int & >( this->calledCount )++;

            return this->RETURNS_MAPPING_INDEX;
        }
    };

    class Mapping_pressButtonForChangeMappingTest : public ::testing::Test
    {
    public:
        void test(
            const int           _SET_HANDLER_KEY
            , const int         _PRESS_BUTTON_KEY
            , const std::size_t _MAPPING_INDEX
            , const std::size_t _CURRENT_MAPPING_INDEX
            , const std::size_t _RETURNS_MAPPING_INDEX
            , const std::size_t _EXPECTED_NEW_MAPPING_INDEX
            , const std::size_t _EXPECTED_MAPPING_INDEX
            , const int         _EXPECTED_CALLED_COUNT
        ) const
        {
            auto    calledCount = 0;
            auto    mappingIndex = _MAPPING_INDEX;

            auto    handlerUnique = Mapping::handlerUnique(
                new TestHandlerForChangeMapping(
                    calledCount
                    , _RETURNS_MAPPING_INDEX
                    , _EXPECTED_MAPPING_INDEX
                )
            );

            auto    mapping = Mapping();

            mapping.setHandler(
                _SET_HANDLER_KEY
                , std::move( handlerUnique )
            );

            EXPECT_EQ(
                _EXPECTED_NEW_MAPPING_INDEX
                , mapping.pressButton(
                    _PRESS_BUTTON_KEY
                    , mappingIndex
                    , _CURRENT_MAPPING_INDEX
                )
            );

            EXPECT_EQ( _EXPECTED_CALLED_COUNT, calledCount );
        }
    };
}

TEST_F(
    Mapping_pressButtonForChangeMappingTest
    , ExistsHandler
)
{
    this->test(
        10
        , 10
        , 20
        , 30
        , 40
        , 40
        , 20
        , 1
    );
}

TEST_F(
    Mapping_pressButtonForChangeMappingTest
    , NotExistsHandler
)
{
    this->test(
        10
        , 20
        , 30
        , 40
        , 50
        , 40
        , 0
        , 0
    );
}
