#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLER_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLER_H

#include "tktemotejoy/generatehandler/withrange.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/typeerror.h"
#include <linux/input.h>
#include <string>
#include <utility>

template<
    typename GENERATE_TO_BUTTON_HANDLER_UNIQUE_T
    , typename GENERATE_HANDLER_UNIQUE_T
>
class GenerateToButtonHandlerUnique
    : public GenerateHandlerWithRangeUnique<
        GenerateToButtonHandlerUnique<
            GENERATE_TO_BUTTON_HANDLER_UNIQUE_T
            , GENERATE_HANDLER_UNIQUE_T
        >
    >
{
public:
    auto generateHandler(
        const Json::object_t &  _OBJECT
        , const __s32           _MIN
        , const __s32           _MAX
        , const __s32           _DEAD_ZONE
    ) const
    {
        const auto  KEY_HANDLER = std::string( "handler" );

        const auto &    OBJECT = getJsonObjectFromObject(
            _OBJECT
            , KEY_HANDLER
        );

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()( OBJECT );
        if( handlerUnique.get() == nullptr ) {
            throw typeIsUnsupported(
                OBJECT
                , KEY_HANDLER
            );
        }

        return GENERATE_TO_BUTTON_HANDLER_UNIQUE_T()(
            _MIN
            , _MAX
            , _DEAD_ZONE
            , std::move( handlerUnique )
        );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLER_H
