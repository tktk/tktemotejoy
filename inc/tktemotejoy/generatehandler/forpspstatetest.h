#ifndef TKTEMOTEJOY_GENERATEHANDLER_FORPSPSTATETEST_H
#define TKTEMOTEJOY_GENERATEHANDLER_FORPSPSTATETEST_H

#include "tktemotejoy/test.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/customjson.h"
#include "nlohmann/json.hpp"
#include <string>
#include <utility>

template< typename GENERATE_HANDLER_UNIQUE_T >
class GenerateHandlerForPspStateTest : public ::testing::Test
{
    struct SetHandler
    {
        template< typename HANDLER_UNIQUE_T >
        void operator()(
            Mapping &               _mapping
            , const std::size_t     _INDEX
            , HANDLER_UNIQUE_T &&   _handlerUnique
        ) const
        {
            _mapping.setHandler(
                _INDEX
                , std::move( _handlerUnique )
            );
        }
    };

    struct SetHandlerWithAssertAnyThrow
    {
        template< typename HANDLER_UNIQUE_T >
        void operator()(
            Mapping &               _mapping
            , const std::size_t     _INDEX
            , HANDLER_UNIQUE_T &&   _handlerUnique
        ) const
        {
            ASSERT_ANY_THROW(
                {
                    _mapping.setHandler(
                        _INDEX
                        , std::move( _handlerUnique )
                    );
                }
            );
        }
    };

    template< typename SET_HANDLER_T >
    void test(
        const std::string &     _JSON
        , const PspState::Bits  _EXPECTED_BITS
    ) const
    {
        const auto  JSON = Json::parse( _JSON );

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( JSON );
        ASSERT_NE( nullptr, handlerUnique.get() );

        auto    mapping = Mapping();

        SET_HANDLER_T()(
            mapping
            , 0
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
        const std::string &     _JSON
        , const PspState::Bits  _EXPECTED_BITS
    ) const
    {
        this->test< SetHandler >(
            _JSON
            , _EXPECTED_BITS
        );
    }

    void testAnyThrow(
        const std::string &     _JSON
    ) const
    {
        this->test< SetHandlerWithAssertAnyThrow >(
            _JSON
            , 0
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_FORPSPSTATETEST_H
