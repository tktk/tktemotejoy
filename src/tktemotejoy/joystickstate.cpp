#include "tktemotejoy/joystickstate.h"

JoystickState::JoystickState(
    const JoystickState::States::size_type      _BUTTONS
    , const JoystickState::States::size_type    _AXES
)
    : buttonStates( _BUTTONS )
    , axisStates( _AXES )
{
}

void JoystickState::setButtonState(
    const JoystickState::States::size_type      _INDEX
    , const JoystickState::States::value_type   _VALUE
)
{
    this->buttonStates.assign(
        _INDEX
        , _VALUE
    );
}

void JoystickState::setAxisState(
    const JoystickState::States::size_type      _INDEX
    , const JoystickState::States::value_type   _VALUE
)
{
    this->axisStates.assign(
        _INDEX
        , _VALUE
    );
}

void JoystickState::forPressedButtons(
    const JoystickState::MapProc &  _MAP_PROC
)
{
    //TODO
}

void JoystickState::forAxes(
    const JoystickState::MapProc &  _MAP_PROC
)
{
    //TODO
}
