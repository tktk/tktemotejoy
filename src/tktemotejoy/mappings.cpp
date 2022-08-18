#include "tktemotejoy/mappings.h"
#include "tktemotejoy/pspstate.h"
#include "tktemotejoy/joystickstate.h"
#include <utility>

namespace {
    bool changeMappingIndex(
        Mappings::Impl::size_type &         _currentMappingIndex
        , const Mappings::Impl::size_type   _NEW_MAPPING_INDEX
    )
    {
        const auto  CHANGED_MAPPING_INDEX = _currentMappingIndex != _NEW_MAPPING_INDEX;
        _currentMappingIndex = _NEW_MAPPING_INDEX;

        return CHANGED_MAPPING_INDEX;
    }

    void changeMappingIndex(
        Mappings::Impl::size_type &     _mappingIndex
        , Mappings::Impl::size_type &   _currentMappingIndex
        , const Mappings::Impl &        _MAPPINGS_IMPL
        , const JoystickState &         _JOYSTICK_STATE
    )
    {
        auto    mappingIndex = _mappingIndex;   //REMOVEME

        while( true ) {
            if( _JOYSTICK_STATE.forPressedButtons(
                [
                    &mappingIndex
                    , &_currentMappingIndex
                    , &_MAPPINGS_IMPL
                ]
                (
                    const JoystickState::States::size_type  _INDEX
                ) -> bool
                {
                    return changeMappingIndex(
                        _currentMappingIndex
                        , _MAPPINGS_IMPL.at( _currentMappingIndex ).pressButton(
                            _INDEX
                            //TODO
                            , mappingIndex
/*
                            , _mappingIndex
*/
                            , _currentMappingIndex
                        )
                    );
                }
            ) == true ) {
                continue;
            }
            if( _JOYSTICK_STATE.forAxes(
                [
                    &mappingIndex
                    , &_currentMappingIndex
                    , &_MAPPINGS_IMPL
                ]
                (
                    const JoystickState::States::size_type      _INDEX
                    , const JoystickState::States::value_type   _VALUE
                ) -> bool
                {
                    return changeMappingIndex(
                        _currentMappingIndex
                        , _MAPPINGS_IMPL.at( _currentMappingIndex ).operateAxis(
                            _INDEX
                            , _VALUE
                            //TODO
                            , mappingIndex
/*
                            , _mappingIndex
*/
                            , _currentMappingIndex
                        )
                    );
                }
            ) == true ) {
                continue;
            }

            break;
        }
    }
}

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
    auto    currentMappingIndex = this->mappingIndex;

    changeMappingIndex(
        this->mappingIndex
        , currentMappingIndex
        , this->IMPL
        , _JOYSTICK_STATE
    );

    _JOYSTICK_STATE.forPressedButtons(
        [
            this
            , &_pspState
            , &currentMappingIndex
        ]
        (
            const JoystickState::States::size_type  _INDEX
        ) -> bool
        {
            this->IMPL.at( currentMappingIndex ).pressButton(
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
            , &currentMappingIndex
        ]
        (
            const JoystickState::States::size_type      _INDEX
            , const JoystickState::States::value_type   _VALUE
        ) -> bool
        {
            this->IMPL.at( currentMappingIndex ).operateAxis(
                _INDEX
                , _VALUE
                , _pspState
            );

            return false;
        }
    );
}
