#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERS_H

#include "tktemotejoy/generatehandler/withrange.h"
#include "tktemotejoy/customjson.h"
#include "tktemotejoy/json.h"
#include "tktemotejoy/typeerror.h"
#include <linux/input.h>
#include <string>
#include <utility>

template<
    typename GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T
    , typename GENERATE_HANDLER_UNIQUE_T
    , typename GENERATE_DUMMY_HANDLER_UNIQUE_T
>
class GenerateToButtonHandlersUnique
    : public GenerateHandlerWithRangeUnique<
        GenerateToButtonHandlersUnique<
            GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T
            , GENERATE_HANDLER_UNIQUE_T
            , GENERATE_DUMMY_HANDLER_UNIQUE_T
        >
    >
{
public:
    template< typename ... ARGS_T >
    auto generateHandler(
        const Json::object_t &  _OBJECT
        , const __s32           _MIN
        , const __s32           _MAX
        , const __s32           _DEAD_ZONE
        , const ARGS_T & ...    _ARGS
    ) const
    {
        const auto  KEY_HANDLER_MINUS = std::string( "handlerMinus" );
        const auto  KEY_HANDLER_PLUS = std::string( "handlerPlus" );

        auto    handlerMinusUnique = generateChildHandler(
            _OBJECT
            , KEY_HANDLER_MINUS
            , _ARGS ...
        );
        auto    handlerPlusUnique = generateChildHandler(
            _OBJECT
            , KEY_HANDLER_PLUS
            , _ARGS ...
        );

        return GENERATE_TO_BUTTON_HANDLERS_UNIQUE_T()(
            _MIN
            , _MAX
            , _DEAD_ZONE
            , std::move( handlerMinusUnique )
            , std::move( handlerPlusUnique )
        );
    }

private:
    template< typename ... ARGS_T >
    auto generateChildHandler(
        const Json::object_t &  _OBJECT
        , const std::string &   _KEY
        , const ARGS_T & ...    _ARGS
    ) const
    {
        const auto  HANDLER_PTR = getJsonObjectFromObjectNotRequired(
            _OBJECT
            , _KEY
        );
        if( HANDLER_PTR == nullptr ) {
            return GENERATE_DUMMY_HANDLER_UNIQUE_T()();
        }
        const auto &    HANDLER = *HANDLER_PTR;

        auto    handlerUnique = GENERATE_HANDLER_UNIQUE_T()(
            HANDLER
            , _ARGS ...
        );
        if( handlerUnique.get() == nullptr ) {
            throw typeIsUnsupported(
                HANDLER
                , _KEY
            );
        }

        return handlerUnique;
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOBUTTONHANDLERS_H
