#include "tktemotejoy/pspstate.h"

namespace {
    struct Bits_
    {
        alignas( 1 ) unsigned short buttons;
        alignas( 1 ) unsigned char  axisX;
        alignas( 1 ) unsigned char  axisY;
    };
}

#define SET( _NAME, _VALUE ) reinterpret_cast< Bits_ & >( this->bits )._NAME = _VALUE;

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
    const PspState::Buttons _VALUE
)
{
    SET(
        buttons
        , _VALUE
    )
}

void PspState::operateAxisX(
    const PspState::Axis    _VALUE
)
{
    SET(
        axisX
        , _VALUE
    )
}

void PspState::operateAxisY(
    const PspState::Axis    _VALUE
)
{
    SET(
        axisY
        , _VALUE
    )
}
