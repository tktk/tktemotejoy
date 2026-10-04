#ifndef TKTEMOTEJOY_GENERATEHANDLER_GENERATEPRESSBUTTONHANDLERFORPSPSTATETEST_H
#define TKTEMOTEJOY_GENERATEHANDLER_GENERATEPRESSBUTTONHANDLERFORPSPSTATETEST_H

#include "tktemotejoy/test.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include <string>
#include <utility>

template< typename GENERATE_HANDLER_UNIQUE_T >
class GeneratePressButtonHandlerForPspStateTestTmpl : public ::testing::Test
{
public:
    void test(
        const std::string &                 _JSON_STRING
        , const tktemotejoy::PspState::Bits _EXPECTED_BITS
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( JSON );
        ASSERT_NE( nullptr, handlerUnique.get() );

        auto    mapping = tktemotejoy::Mapping(
            1
            , 0
        );

        mapping.setHandler(
            0
            , std::move( handlerUnique )
        );

        auto    pspState = tktemotejoy::PspState();

        mapping.pressButton(
            0
            , pspState
        );

        const auto  OTHER = tktemotejoy::PspState();

        auto    bits = tktemotejoy::PspState::Bits();

        pspState.diff(
            OTHER
            , [
                &bits
            ]
            (
                const tktemotejoy::PspState::Bits & _BITS
            )
            {
                bits = _BITS;
            }
        );

        EXPECT_EQ( _EXPECTED_BITS, bits );
    }

    void testAnyThrow(
        const std::string &     _JSON_STRING
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        EXPECT_ANY_THROW( GENERATE_HANDLER_UNIQUE_T()( JSON ) );
    }

    void testNull(
        const std::string &     _JSON_STRING
    ) const
    {
        const auto  JSON = Json::parse( _JSON_STRING );

        const auto  HANDLER_UNIQUE = GENERATE_HANDLER_UNIQUE_T()( JSON );
        ASSERT_EQ( nullptr, HANDLER_UNIQUE.get() );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_GENERATEPRESSBUTTONHANDLERFORPSPSTATETEST_H
