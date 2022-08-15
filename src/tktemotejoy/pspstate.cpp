#include "tktemotejoy/pspstate.h"

namespace {
    struct BitField
    {
        alignas( 1 ) unsigned short buttons;
        alignas( 1 ) unsigned char  axisX;
        alignas( 1 ) unsigned char  axisY;
    };
}

#define SET_BITS( _NAME, _VALUE ) reinterpret_cast< BitField & >( this->bits )._NAME = _VALUE;

#define PRESS_BUTTON( _NAME ) SET_BITS( _NAME, true )

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

void PspState::pressButtons(
    const PspState::Buttons _BUTTONS
)
{
    //TODO
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
