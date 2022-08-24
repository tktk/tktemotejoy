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
    , typename GENERATE_HANDLER_UNIQUE_T
    , typename GENERATE_DUMMY_HANDLER_UNIQUE_T
>
class GenerateToButtonHandlersUnique
    : public GenerateHandlerWithDeadZoneUnique<
        GenerateToButtonHandlersUnique<
            GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T
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

        auto    handler1Unique = generateHandler(
            _OBJECT
            , KEY_HANDLER1
        );
        auto    handler2Unique = generateHandler(
            _OBJECT
            , KEY_HANDLER2
        );

        return GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T()(
            _DEAD_ZONE
            , std::move( handler1Unique )
            , std::move( handler2Unique )
        );
    }

private:
    auto generateHandler(
        const Json::object_t &  _OBJECT
        , const std::string &   _KEY
    ) const
    {
        const auto  IT = _OBJECT.find( _KEY );
        if( IT == _OBJECT.end() ) {
            return GENERATE_DUMMY_HANDLER_UNIQUE_T()();
        } else {
            const auto &    HANDLER_JSON = IT->second;
            if( HANDLER_JSON.is_object() == false ) {
                throw jsonIsNotObject( _KEY );
            }

            const auto &    HANDLER = HANDLER_JSON.get_ref< const Json::object_t & >();

            return GENERATE_HANDLER_UNIQUE_T()( HANDLER );
        }
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERS_H
