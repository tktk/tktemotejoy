#include "tktemotejoy/generatehandler/tobuttons.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/customjson.h"
#include <sstream>
#include <stdexcept>

namespace {
    const auto  KEY_BUTTONS = "buttons";
}

Mapping::PressButtonHandlerForPspStateUnique generateToButtonsUnique(
    const Json::object_t &  _OBJECT
)
{
    const auto  STRING_TO_BUTTON = std::map< std::string, PspState::Buttons >(
        {
            { "up", PspState::Button::UP },
            { "down", PspState::Button::DOWN },
            { "left", PspState::Button::LEFT },
            { "right", PspState::Button::RIGHT },
            { "circle", PspState::Button::CIRCLE },
            { "cross", PspState::Button::CROSS },
            { "triangle", PspState::Button::TRIANGLE },
            { "square", PspState::Button::SQUARE },
            { "triggerL", PspState::Button::TRIGGER_L },
            { "triggerR", PspState::Button::TRIGGER_R },
            { "start", PspState::Button::START },
            { "select", PspState::Button::SELECT },
        }
    );

    const auto  OBJECT_END = _OBJECT.end();

    const auto  BUTTONS_IT = _OBJECT.find( KEY_BUTTONS );
    if( BUTTONS_IT == OBJECT_END ) {
        auto    oStringStream = std::ostringstream();

        oStringStream << '"' << KEY_BUTTONS << '"' << "が存在しない";

        throw std::runtime_error( oStringStream.str() );
    }
    const auto &    BUTTON_STRINGS_JSON = BUTTONS_IT->second;

    if( BUTTON_STRINGS_JSON.is_array() == false ) {
        auto    oStringStream = std::ostringstream();

        oStringStream << '"' << KEY_BUTTONS << '"' << "がリストではない";

        throw std::runtime_error( oStringStream.str() );
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
