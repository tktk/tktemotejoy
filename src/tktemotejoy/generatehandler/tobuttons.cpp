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

    const auto &    BUTTON_STRINGS_JSON = _OBJECT.at( KEY_BUTTONS );

    const auto &    BUTTON_STRINGS = BUTTON_STRINGS_JSON.get_ref< const Json::array_t & >();

    auto    buttons = PspState::Buttons( 0 );

    const auto  END = STRING_TO_BUTTON.end();
    for( const auto & BUTTON_STRING : BUTTON_STRINGS ) {
        const auto  IT = STRING_TO_BUTTON.find( BUTTON_STRING );
        if( IT == END ) {
            auto    oStringStream = std::ostringstream();

            oStringStream << "ボタン" << BUTTON_STRING << "は非対応";

            throw std::runtime_error( oStringStream.str() );
        }

        buttons |= IT->second;
    }

    return Mapping::handlerUnique( new ToButtons( buttons ) );
}
