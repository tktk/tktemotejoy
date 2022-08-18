#include "tktemotejoy/mappings.h"
#include "tktemotejoy/mapping.h"
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
        while( true ) {
            if( _JOYSTICK_STATE.forPressedButtons(
                [
                    &_mappingIndex
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
                            , _mappingIndex
                            , _currentMappingIndex
                        )
                    );
                }
            ) == true ) {
                continue;
            }
            if( _JOYSTICK_STATE.forAxes(
                [
                    &_mappingIndex
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
                            , _mappingIndex
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

    void joystickStateToPspState(
        PspState &              _pspState
        , const Mapping &       _MAPPING
        , const JoystickState & _JOYSTICK_STATE
    )
    {
        _JOYSTICK_STATE.forPressedButtons(
            [
                &_pspState
                , &_MAPPING
            ]
            (
                const JoystickState::States::size_type  _INDEX
            ) -> bool
            {
                _MAPPING.pressButton(
                    _INDEX
                    , _pspState
                );

                return false;
            }
        );
        _JOYSTICK_STATE.forAxes(
            [
                &_pspState
                , &_MAPPING
            ]
            (
                const JoystickState::States::size_type      _INDEX
                , const JoystickState::States::value_type   _VALUE
            ) -> bool
            {
                _MAPPING.operateAxis(
                    _INDEX
                    , _VALUE
                    , _pspState
                );

                return false;
            }
        );
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

    ::changeMappingIndex(
        this->mappingIndex
        , currentMappingIndex
        , this->IMPL
        , _JOYSTICK_STATE
    );

    ::joystickStateToPspState(
        _pspState
        , this->IMPL.at( currentMappingIndex )
        , _JOYSTICK_STATE
    );
}
