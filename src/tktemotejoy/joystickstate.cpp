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
    this->buttonStates.at( _INDEX ) = _VALUE;
}

void JoystickState::setAxisState(
    const JoystickState::States::size_type      _INDEX
    , const JoystickState::States::value_type   _VALUE
)
{
    this->axisStates.at( _INDEX ) = _VALUE;
}

bool JoystickState::forPressedButtons(
    const JoystickState::ForButton &    _FOR_BUTTON
) const
{
    auto    index = JoystickState::States::size_type( 0 );
    for( const auto & STATE : this->buttonStates ) {
        if( STATE != 0 ) {
            if( _FOR_BUTTON( index ) == true ) {
                return true;
            }
        }

        index++;
    }

    return false;
}

bool JoystickState::forAxes(
    const JoystickState::ForAxis &  _FOR_AXIS
) const
{
    auto    index = JoystickState::States::size_type( 0 );
    for( const auto & STATE : this->axisStates ) {
        if( _FOR_AXIS(
            index
            , STATE
        ) == true ) {
            return true;
        }

        index++;
    }

    return false;
}
