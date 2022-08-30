#include "tktemotejoy/pspstate.h"

namespace {
    union Bits_
    {
        struct
        {
            alignas( 1 ) unsigned short buttons;
            alignas( 1 ) unsigned char  axisX;
            alignas( 1 ) unsigned char  axisY;
        };
        PspState::Bits  bits;
    };

    enum {
        BITS_DEFAULT = 0x80800000,
    };
}

PspState::PspState(
)
    : bits( BITS_DEFAULT )
{
}

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
    reinterpret_cast< Bits_ & >( this->bits ).buttons |= _VALUE;
}

void PspState::operateAxisX(
    const PspState::Axis    _VALUE
)
{
    reinterpret_cast< Bits_ & >( this->bits ).axisX = _VALUE;
}

void PspState::operateAxisY(
    const PspState::Axis    _VALUE
)
{
    reinterpret_cast< Bits_ & >( this->bits ).axisY = _VALUE;
}
