#ifndef TKTEMOTEJOY_EVDEVSTATE_H
#define TKTEMOTEJOY_EVDEVSTATE_H

#include <linux/input.h>
#include <vector>
#include <functional>

class EvdevState final
{
public:
    using States = std::vector< __s32 >;

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
    EvdevState(
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

#endif  // TKTEMOTEJOY_EVDEVSTATE_H
