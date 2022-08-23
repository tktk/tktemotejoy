#ifndef TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXIS_H
#define TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXIS_H

#include "tktemotejoy/customjson.h"
#include "tktemotejoy/jsonerror.h"
#include <linux/joystick.h>
#include <string>

template< typename GENERATE_TO_FIXED_AXIS_UNIQUE_T >
class GenerateToFixedAxisUnique
{
public:
    auto operator()(
        const Json::object_t &  _OBJECT
    ) const
    {
        const auto  KEY_VALUE = std::string( "value" );

        __s16   value;

        const auto  IT = _OBJECT.find( KEY_VALUE );
        if( IT == _OBJECT.end() ) {
            throw jsonIsNotExists( KEY_VALUE );
        } else {
            const auto &    VALUE_JSON = IT->second;
            //TODO
/*
            if( VALUE_JSON.is_number_integer() == false ) {
                throw jsonIsNotInteger( KEY_VALUE );
            }
*/

            const auto &    VALUE = VALUE_JSON.get_ref< const Json::number_integer_t & >();

            value = VALUE;
        }

        return GENERATE_TO_FIXED_AXIS_UNIQUE_T()( value );
    }
};

#endif  // TKTEMOTEJOY_GENERATEHANDLER_TOFIXEDAXIS_H
