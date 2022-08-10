#ifndef TKTEMOTEJOY_JOYSTICKSTATE_H
#define TKTEMOTEJOY_JOYSTICKSTATE_H

#include <linux/joystick.h>
#include <vector>
#include <functional>

class JoystickState
{
public:
    using States = std::vector< __s16 >;

    using MapProc = std::function<
        bool (
            const States::size_type
            , const States::value_type
        )
    >;

private:
    States  buttonStates;
    States  axisStates;

public:
    JoystickState(
        const States::size_type
        , const States::size_type
    );

    void setButtonState(
        const States::size_type
        , const States::value_type
    );

    void setAxisState(
        const States::size_type
        , const States::value_type
    );

    void forPressedButtons(
        const MapProc &
    );

    void forAxes(
        const MapProc &
    );
};

#endif  // TKTEMOTEJOY_JOYSTICKSTATE_H
