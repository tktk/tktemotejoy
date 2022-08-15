#include "tktemotejoy/pspstate.h"

namespace {
    struct BitField
    {
        bool    select : 1;

        bool : 2;

        bool    start : 1;
        bool    up : 1;
        bool    right : 1;
        bool    down : 1;
        bool    left : 1;
        bool    triggerL : 1;
        bool    triggerR : 1;

        bool : 2;

        bool    triangle : 1;
        bool    circle : 1;
        bool    cross : 1;
        bool    square : 1;

        unsigned char axisX;
        unsigned char axisY;
    };
}

#define SET_BITS( _NAME, _VALUE ) reinterpret_cast< BitField & >( this->bits )._NAME = _VALUE;

#define PRESS_BUTTON( _NAME ) SET_BITS( _NAME, 1 )

#define OPERATE_AXIS( _NAME, _VALUE ) SET_BITS( _NAME, _VALUE )

void PspState::diff(
    const PspState &                _OTHER
    , const PspState::WhenDiff &    _WHEN_DIFF
) const
{
    if( this->bits != _OTHER.bits ) {
        _WHEN_DIFF( this->bits );
    }
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
    const PspState::Axis    _value
)
{
    OPERATE_AXIS(
        axisX
        , _value
    )
}

void PspState::operateAxisY(
    const PspState::Axis    _value
)
{
    OPERATE_AXIS(
        axisY
        , _value
    )
}
