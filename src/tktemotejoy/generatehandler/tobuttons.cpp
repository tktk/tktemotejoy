#include "tktemotejoy/generatehandler/tobuttons.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"
#include "tktemotejoy/mapping.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/customjson.h"

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

    const auto &    STRINGS_JSON = _OBJECT.at( KEY_BUTTONS );

    const auto &    STRINGS = STRINGS_JSON.get_ref< const Json::array_t & >();

    auto    buttons = PspState::Buttons( 0 );
    for( const auto & STRING : STRINGS ) {
        const auto  IT = STRING_TO_BUTTON.find( STRING );

        buttons |= IT->second;
    }

    return Mapping::handlerUnique( new ToButtons( buttons ) );
}
