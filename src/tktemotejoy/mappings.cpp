#include "tktemotejoy/mappings.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/joystickstate.h"
#include <utility>

Mappings::Mappings(
    Mappings::Impl &&                   _impl
    , const Mappings::Impl::size_type   _DEFAULT_MAPPING_INDEX
)
    : IMPL( std::move( _impl ) )
    , mappingIndex( _DEFAULT_MAPPING_INDEX )
{
}

void Mappings::joystickStateToPspState(
    PspState &              _pspState
    , const JoystickState & _JOYSTICK_STATE
)
{
    _JOYSTICK_STATE.forPressedButtons(
        [
            this
            , &_pspState
        ]
        (
            const JoystickState::States::size_type  _INDEX
        ) -> bool
        {
            this->IMPL.at( 0 ).pressButton(
                _INDEX
                , _pspState
            );

            return false;
        }
    );
    _JOYSTICK_STATE.forAxes(
        [
            this
            , &_pspState
        ]
        (
            const JoystickState::States::size_type      _INDEX
            , const JoystickState::States::value_type   _VALUE
        ) -> bool
        {
            this->IMPL.at( 0 ).operateAxis(
                _INDEX
                , _VALUE
                , _pspState
            );

            return false;
        }
    );
}
