#include "tktemotejoy/test.h"
#include "tktemotejoy/evdevstate.h"
#include <map>

namespace {
    using IndexAndValueMap = std::map<
        EvdevState::States::size_type
        , EvdevState::States::value_type
    >;

    class EvdevState_forAxesTest : public ::testing::Test
    {
    public:
        void test(
            EvdevState                              _evdevState
            , const IndexAndValueMap                _INDEX_AND_VALUE_MAP
            , const bool                            _RETURNS_FOR_STATE
            , const bool                            _EXPECTED
            , const EvdevState::States::size_type   _EXPECTED_CALL_COUNT
            , const IndexAndValueMap                _EXPECTED_CALLED_INDEX_AND_VALUE_MAP
            , const bool                            _TEST_CALLED_INDEX_AND_VALUE_MAP
        ) const
        {
            for( const auto & INDEX_AND_VALUE : _INDEX_AND_VALUE_MAP ) {
                _evdevState.setAxisState(
                    INDEX_AND_VALUE.first
                    , INDEX_AND_VALUE.second
                );
            }

            auto    callCount = 0;
            auto    calledIndexAndValueMap = IndexAndValueMap();
            EXPECT_EQ(
                _EXPECTED
                , _evdevState.forAxes(
                    [
                        &_RETURNS_FOR_STATE
                        , &callCount
                        , &calledIndexAndValueMap
                    ]
                    (
                        const EvdevState::States::size_type     _INDEX
                        , const EvdevState::States::value_type  _VALUE
                    ) -> bool
                    {
                        callCount++;
                        calledIndexAndValueMap.insert( { _INDEX, _VALUE } );

                        return _RETURNS_FOR_STATE;
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
    EvdevState_forAxesTest
    , ForAllAxes
)
{
    this->test(
        EvdevState(
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
    EvdevState_forAxesTest
    , Breaked
)
{
    this->test(
        EvdevState(
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
