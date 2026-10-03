#include "tktemotejoy/test.h"
#include "tktemotejoy/evdevstate.h"
#include <vector>
#include <set>

namespace {
    using Indices = std::set< EvdevState::States::size_type >;

    class EvdevState_forPressedButtonsTest : public ::testing::Test
    {
    public:
        void test(
            EvdevState                              _evdevState
            , const Indices                         _PRESS_BUTTON_INDICES
            , const bool                            _RETURNS_FOR_STATE
            , const bool                            _EXPECTED
            , const EvdevState::States::size_type   _EXPECTED_CALL_COUNT
            , const bool                            _TEST_CALLED_INDICES
        ) const
        {
            for( const auto & INDEX : _PRESS_BUTTON_INDICES ) {
                _evdevState.setButtonState(
                    INDEX
                    , 1
                );
            }

            auto    callCount = 0;
            auto    calledIndices = Indices();
            EXPECT_EQ(
                _EXPECTED
                , _evdevState.forPressedButtons(
                    [
                        &_RETURNS_FOR_STATE
                        , &callCount
                        , &calledIndices
                    ]
                    (
                        const EvdevState::States::size_type _INDEX
                    ) -> bool
                    {
                        callCount++;
                        calledIndices.insert( _INDEX );

                        return _RETURNS_FOR_STATE;
                    }
                )
            );

            EXPECT_EQ( _EXPECTED_CALL_COUNT, callCount );
            if( _TEST_CALLED_INDICES == true ) {
                EXPECT_EQ( _PRESS_BUTTON_INDICES, calledIndices );
            }
        }
    };
}

TEST_F(
    EvdevState_forPressedButtonsTest
    , ForAllPressedButtons
)
{
    this->test(
        EvdevState(
            5
            , 5
        )
        , Indices{
            1
            , 2
            , 3
        }
        , false
        , false
        , 3
        , true
    );
}

TEST_F(
    EvdevState_forPressedButtonsTest
    , Breaked
)
{
    this->test(
        EvdevState(
            5
            , 5
        )
        , Indices{
            1
            , 2
            , 3
        }
        , true
        , true
        , 1
        , false
    );
}
