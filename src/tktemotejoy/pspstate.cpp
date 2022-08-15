#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    struct ButtonBits_
    {
        bool : 4;
        bool up : 1;
    };
}

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
    reinterpret_cast< ButtonBits_ & >( this->buttonBits ).up = 1;
}


void PspState::pressDown(
)
{
    //TODO
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
