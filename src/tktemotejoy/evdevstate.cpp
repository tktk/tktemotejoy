#include "tktemotejoy/evdevstate.h"

EvdevState::EvdevState(
    const EvdevState::States::size_type     _BUTTONS
    , const EvdevState::States::size_type   _AXES
)
    : buttonStates( _BUTTONS )
    , axisStates( _AXES )
{
}

void EvdevState::setButtonState(
    const EvdevState::States::size_type     _INDEX
    , const EvdevState::States::value_type  _VALUE
)
{
    this->buttonStates.at( _INDEX ) = _VALUE;
}

void EvdevState::setAxisState(
    const EvdevState::States::size_type     _INDEX
    , const EvdevState::States::value_type  _VALUE
)
{
    this->axisStates.at( _INDEX ) = _VALUE;
}

bool EvdevState::forPressedButtons(
    const EvdevState::ForButton &   _FOR_BUTTON
) const
{
    auto    index = EvdevState::States::size_type( 0 );
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

bool EvdevState::forAxes(
    const EvdevState::ForAxis & _FOR_AXIS
) const
{
    auto    index = EvdevState::States::size_type( 0 );
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
