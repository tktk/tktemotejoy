#include "tktemotejoy/joystickstate.h"
#include <cstdio>

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
    this->buttonStates.at( _INDEX ) = _VALUE;
}

void JoystickState::setAxisState(
    const JoystickState::States::size_type      _INDEX
    , const JoystickState::States::value_type   _VALUE
)
{
    this->axisStates.at( _INDEX ) = _VALUE;
}

void JoystickState::forPressedButtons(
    const JoystickState::ForProc &  _FOR_PROC
)
{
    auto    index = JoystickState::States::size_type( 0 );
    for( const auto & STATE : this->buttonStates ) {
        if( STATE != 0 ) {
            _FOR_PROC(
                index
                , STATE
            );
        }

        index++;
    }
}

void JoystickState::forAxes(
    const JoystickState::ForProc &  _FOR_PROC
)
{
    //TODO
}
