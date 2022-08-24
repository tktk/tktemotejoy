#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERS_H

#include "tktemotejoy/generatehandler/withdeadzone.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"
#include <linux/joystick.h>
#include <string>
#include <utility>

template<
    typename GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T
    , typename HANDLER_UNIQUE_T
    , typename GENERATE_HANDLER_UNIQUE_T
    , typename GENERATE_DUMMY_HANDLER_UNIQUE_T
>
class GenerateToButtonHandlersUnique
    : public GenerateHandlerWithDeadZoneUnique<
        GenerateToButtonHandlersUnique<
            GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T
            , HANDLER_UNIQUE_T
            , GENERATE_HANDLER_UNIQUE_T
            , GENERATE_DUMMY_HANDLER_UNIQUE_T
        >
    >
{
public:
    auto operatorCallImpl(
        const Json::object_t &  _OBJECT
        , const __s16           _DEAD_ZONE
    ) const
    {
        const auto  KEY_HANDLER1 = std::string( "handler1" );
        const auto  KEY_HANDLER2 = std::string( "handler2" );

        auto    handler1Unique = HANDLER_UNIQUE_T();

        //TODO
/*
        const auto  HANDLER1_IT = _OBJECT.find( KEY_HANDLER1 );
        if( HANDLER1_IT == _OBJECT.end() ) {
            handler1Unique = GENERATE_DUMMY_HANDLER_UNIQUE_T()();
        } else {
            const auto &    HANDLER = HANDLER1_IT->second.get_ref< const Json::object & >();

            handler1Unique = GENERATE_HANDLER_UNIQUE_T()( HANDLER );
        }
*/

        auto    handler2Unique = HANDLER_UNIQUE_T();

        //TODO
/*
        const auto  HANDLER2_IT = _OBJECT.find( KEY_HANDLER2 );
        if( HANDLER2_IT == _OBJECT.end() ) {
            handler2Unique = GENERATE_DUMMY_HANDLER_UNIQUE_T()();
        } else {
            const auto &    HANDLER = HANDLER2_IT->second.get_ref< const Json::object & >();

            handler2Unique = GENERATE_HANDLER_UNIQUE_T()( HANDLER );
        }
*/

        return GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T()(
            _DEAD_ZONE
            , std::move( handler1Unique )
            , std::move( handler2Unique )
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERS_H
