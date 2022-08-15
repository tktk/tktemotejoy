#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    struct ButtonBits_
    {
        bool select : 1;

        bool : 2;

        bool start : 1;
        bool up : 1;
        bool right : 1;
        bool down : 1;
        bool left : 1;
        bool triggerL : 1;
        bool triggerR : 1;

        bool : 2;

        bool triangle : 1;
        bool circle : 1;
        bool cross : 1;
        bool square : 1;
    };
}

#define PRESS_BUTTON( _BUTTON ) reinterpret_cast< ButtonBits_ & >( this->buttonBits )._BUTTON = 1;

void PspState::diff(
    const PspState &
    , const WhenDiffButtons &   _WHEN_DIFF_BUTTONS
    , const WhenDiffAxis &
    , const WhenDiffAxis &
) const
{
    _WHEN_DIFF_BUTTONS( this->buttonBits );
}

void PspState::pressUp(
)
{
    PRESS_BUTTON( up )
}

void PspState::pressDown(
)
{
    PRESS_BUTTON( down )
}

void PspState::pressLeft(
)
{
    //TODO
}

void PspState::pressRight(
)
{
    //TODO
}

void PspState::pressCircle(
)
{
    //TODO
}

void PspState::pressCross(
)
{
    //TODO
}

void PspState::pressTriangle(
)
{
    //TODO
}

void PspState::pressSquare(
)
{
    //TODO
}

void PspState::pressTriggerL(
)
{
    //TODO
}

void PspState::pressTriggerR(
)
{
    //TODO
}

void PspState::pressStart(
)
{
    //TODO
}

void PspState::pressSelect(
)
{
    //TODO
}

void PspState::operateAxisX(
    const Axis
)
{
    //TODO
}

void PspState::operateAxisY(
    const Axis
)
{
    //TODO
}
