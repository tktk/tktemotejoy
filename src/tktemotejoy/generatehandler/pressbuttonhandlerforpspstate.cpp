#include "tktemotejoy/generatehandler/pressbuttonhandlerforpspstate.h"
#include "tktemotejoy/customjson.h"

/*
namespace {
    const auto  TYPE = std::string( "toButtons" );
    const auto  KEY_BUTTONS = std::string( "buttons" );

    struct GetType
    {
        const auto & operator()(
        ) const
        {
            return TYPE;
        }
    };

    struct GenerateHandlerUnique
    {
        auto operator()(
            const Json::object_t &  _OBJECT
        ) const
        {
            const auto  OBJECT_END = _OBJECT.end();

            const auto  BUTTONS_IT = _OBJECT.find( KEY_BUTTONS );
            if( BUTTONS_IT == OBJECT_END ) {
                throw jsonIsNotExists(
                    TYPE
                    , KEY_BUTTONS
                );
            }
            const auto &    BUTTON_STRINGS_JSON = BUTTONS_IT->second;

            if( BUTTON_STRINGS_JSON.is_array() == false ) {
                throw jsonIsNotArray(
                    TYPE
                    , KEY_BUTTONS
                );
            }
            const auto &    BUTTON_STRINGS = BUTTON_STRINGS_JSON.get_ref< const Json::array_t & >();

            auto    buttons = PspState::Buttons( 0 );

            const auto  STRING_TO_BUTTON_END = STRING_TO_BUTTON.end();
            for( const auto & BUTTON_STRING : BUTTON_STRINGS ) {
                const auto  IT = STRING_TO_BUTTON.find( BUTTON_STRING );
                if( IT == STRING_TO_BUTTON_END ) {
                    auto    oStringStream = std::ostringstream();

                    oStringStream << "ボタン\"" << BUTTON_STRING << "\"は非対応";

                    throw std::runtime_error( oStringStream.str() );
                }

                buttons |= IT->second;
            }

            return Mapping::handlerUnique( new ToButtons( buttons ) );
        }
    };
}
*/

Mapping::PressButtonHandlerForPspStateUnique generatePressButtonHandlerForPspStateUnique(
    const Json::object_t &  _OBJECT
)
{
    //TODO
    return Mapping::PressButtonHandlerForPspStateUnique();
/*
    return generateHandlerUnique<
        Mapping::PressButtonHandlerForPspStateUnique
        , GetType
        , GenerateHandlerUnique
    >( _OBJECT );
*/
}
