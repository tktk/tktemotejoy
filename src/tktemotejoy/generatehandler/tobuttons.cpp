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
    const auto &    STRINGS_JSON = _OBJECT.at( KEY_BUTTONS );

    const auto &    STRINGS = STRINGS_JSON.get_ref< const Json::array_t & >();

    const auto  STRING_TO_BUTTON = std::map< std::string, PspState::Buttons >(
        {
            { "up", PspState::Button::UP },
            { "down", PspState::Button::DOWN },
        }
    );

    const auto  IT = STRING_TO_BUTTON.find( STRINGS.at( 0 ) );

    return Mapping::handlerUnique( new ToButtons( IT->second ) );
}
