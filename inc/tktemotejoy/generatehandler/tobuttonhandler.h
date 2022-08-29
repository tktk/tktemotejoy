#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLER_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLER_H

#include "tktemotejoy/generatehandler/withdeadzoneunsigned.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/jsonerror.h"
#include <linux/joystick.h>
#include <string>
#include <utility>

template<
    typename GENERATE_TO_BUTTON_HANDLER_UNIQUE_T
    , typename GENERATE_HANDLER_UNIQUE_T
>
class GenerateToButtonHandlerUnique
    : public GenerateHandlerWithDeadZoneUnsignedUnique<
        GenerateToButtonHandlerUnique<
            GENERATE_TO_BUTTON_HANDLER_UNIQUE_T
            , GENERATE_HANDLER_UNIQUE_T
        >
    >
{
public:
    auto operatorCallImpl(
        const Json::object_t &  _OBJECT
        , const __u16           _DEAD_ZONE
    ) const
    {
/*
        const auto  KEY_HANDLER = std::string( "handler" );

        const auto &    OBJECT = getJsonObjectFromObject(
            _OBJECT
            , KEY_HANDLER
        );

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( OBJECT );
*/

        return GENERATE_TO_BUTTON_HANDLER_UNIQUE_T()(
            100
            , nullptr
/*
            _DEAD_ZONE
            , std::move( handlerUnique )
*/
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLER_H
