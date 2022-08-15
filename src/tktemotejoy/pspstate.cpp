#include "tktemotejoy/pspstate.h"

namespace {
    struct BitField
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

#define PRESS_BUTTON( _BUTTON ) reinterpret_cast< BitField & >( this->bits )._BUTTON = 1;

void PspState::diff(
    const PspState &                _OTHER
    , const PspState::WhenDiff &    _WHEN_DIFF
) const
{
    _WHEN_DIFF( this->bits );
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
    PRESS_BUTTON( left )
}

void PspState::pressRight(
)
{
    PRESS_BUTTON( right )
}

void PspState::pressCircle(
)
{
    PRESS_BUTTON( circle )
}

void PspState::pressCross(
)
{
    PRESS_BUTTON( cross )
}

void PspState::pressTriangle(
)
{
    PRESS_BUTTON( triangle )
}

void PspState::pressSquare(
)
{
    PRESS_BUTTON( square )
}

void PspState::pressTriggerL(
)
{
    PRESS_BUTTON( triggerL )
}

void PspState::pressTriggerR(
)
{
    PRESS_BUTTON( triggerR )
}

void PspState::pressStart(
)
{
    PRESS_BUTTON( start )
}

void PspState::pressSelect(
)
{
    PRESS_BUTTON( select )
}

void PspState::operateAxisX(
    const PspState::Axis
)
{
    //TODO
}

void PspState::operateAxisY(
    const PspState::Axis
)
{
    //TODO
}
