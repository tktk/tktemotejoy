#ifndef TKTEMOTEJOY_GENERATEHANDLER_FORPSPSTATETEST_H
#define TKTEMOTEJOY_GENERATEHANDLER_FORPSPSTATETEST_H

#include "tktemotejoy/test.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <utility>

template< typename GENERATE_HANDLER_UNIQUE_T >
class GenerateHandlerForPspStateTest : public ::testing::Test
{
    void test(
        const std::string &     _JSON_STRING
        , const PspState::Bits  _EXPECTED_BITS
        , const bool            _GENERATE_HANDLER_UNIQUE_WITH_ASSERT_ANY_THROW
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        if( _GENERATE_HANDLER_UNIQUE_WITH_ASSERT_ANY_THROW == true ) {
            // ASSERT_ARY_THROWで記述するとsegmentation fault
            try {
                GENERATE_HANDLER_UNIQUE_T()( JSON );

                ASSERT_FALSE( true );
            } catch( ... ) {
                return;
            }
        }

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( JSON );
        ASSERT_NE( nullptr, handlerUnique.get() );

        auto    mapping = Mapping();

        mapping.setHandler(
            0
            , std::move( handlerUnique )
        );

        auto    pspState = PspState();

        mapping.pressButton(
            0
            , pspState
        );

        const auto  OTHER = PspState();

        auto    bits = PspState::Bits();

        pspState.diff(
            OTHER
            , [
                &bits
            ]
            (
                const PspState::Bits &  _BITS
            )
            {
                bits = _BITS;
            }
        );

        EXPECT_EQ( _EXPECTED_BITS, bits );
    }

public:
    void test(
        const std::string &     _JSON_STRING
        , const PspState::Bits  _EXPECTED_BITS
    ) const
    {
        this->test(
            _JSON_STRING
            , _EXPECTED_BITS
            , false
        );
    }

    void testAnyThrow(
        const std::string &     _JSON_STRING
    ) const
    {
        this->test(
            _JSON_STRING
            , 0
            , true
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_FORPSPSTATETEST_H
