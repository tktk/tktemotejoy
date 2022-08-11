#include "fg/util/test.h"
#include "tktemotejoy/joystickstate.h"
#include <map>

namespace {
    using IndexAndValueMap = std::map<
        JoystickState::States::size_type
        , JoystickState::States::value_type
    >;

    class JoystickState_forAxesTest : public ::testing::Test
    {
    public:
        void test(
            JoystickState                               _joystickState
            , const IndexAndValueMap                    _INDEX_AND_VALUE_MAP
            , const bool                                _RETURNS_FOR_PROC
            , const bool                                _EXPECTED
            , const JoystickState::States::size_type    _EXPECTED_CALL_COUNT
            , const IndexAndValueMap                    _EXPECTED_CALLED_INDEX_AND_VALUE_MAP
            , const bool                                _TEST_CALLED_INDEX_AND_VALUE_MAP
        )
        {
            for( const auto & INDEX_AND_VALUE : _INDEX_AND_VALUE_MAP ) {
                _joystickState.setAxisState(
                    INDEX_AND_VALUE.first
                    , INDEX_AND_VALUE.second
                );
            }

            auto    callCount = 0;
            auto    calledIndexAndValueMap = IndexAndValueMap();
            EXPECT_EQ(
                _EXPECTED
                , _joystickState.forAxes(
                    [
                        &_RETURNS_FOR_PROC
                        , &callCount
                        , &calledIndexAndValueMap
                    ]
                    (
                        const JoystickState::States::size_type      _INDEX
                        , const JoystickState::States::value_type   _VALUE
                    ) -> bool
                    {
                        callCount++;
                        calledIndexAndValueMap.insert( { _INDEX, _VALUE } );

                        return _RETURNS_FOR_PROC;
                    }
                )
            );

            EXPECT_EQ( _EXPECTED_CALL_COUNT, callCount );
            if( _TEST_CALLED_INDEX_AND_VALUE_MAP == true ) {
                EXPECT_EQ( _EXPECTED_CALLED_INDEX_AND_VALUE_MAP, calledIndexAndValueMap );
            }
        }
    };
}

TEST_F(
    JoystickState_forAxesTest
    , ForAllAxes
)
{
    this->test(
        JoystickState(
            5
            , 5
        )
        , IndexAndValueMap{
            { 1, 10 }
            , { 2, 20 }
            , { 3, 30 }
        }
        , false
        , false
        , 5
        , IndexAndValueMap{
            { 0, 0 }
            , { 1, 10 }
            , { 2, 20 }
            , { 3, 30 }
            , { 4, 0 }
        }
        , true
    );
}

TEST_F(
    JoystickState_forAxesTest
    , Breaked
)
{
    this->test(
        JoystickState(
            5
            , 5
        )
        , IndexAndValueMap{}
        , true
        , true
        , 1
        , IndexAndValueMap{}
        , false
    );
}
