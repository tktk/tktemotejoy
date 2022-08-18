#ifndef TKTEMOTEJOY_JOYSTICKSTATE_H
#define TKTEMOTEJOY_JOYSTICKSTATE_H

#include <linux/joystick.h>
#include <vector>
#include <functional>

class JoystickState final
{
public:
    using States = std::vector< __s16 >;

    using ForButton = std::function<
        bool (
            const States::size_type
        )
    >;

    using ForAxis = std::function<
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

    bool forPressedButtons(
        const ForButton &
    ) const;

    bool forAxes(
        const ForAxis &
    ) const;
};

#endif  // TKTEMOTEJOY_JOYSTICKSTATE_H
