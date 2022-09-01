#include "tktemotejoy/ctrl.h"
#include "tktemotejoy/hook.h"
#include <pspctrl.h>
#include <pspctrl_kernel.h>
#include <pspsdk.h>

typedef union
{
    struct
    {
        _Alignas( 2 ) unsigned short    buttons;
        _Alignas( 1 ) unsigned char     axisX;
        _Alignas( 1 ) unsigned char     axisY;
    };

    unsigned int    value;
} FromUsbData;

typedef int ( *CtrlBufferFunction )(
    SceCtrlData *
    , const int
    , const int
);

enum {
    INITIALIZE_VALUE = 0x80800000,
};

FromUsbData currentFromUsbData;

static CtrlBufferFunction   originalCtrlPeekBufferPositive;
static CtrlBufferFunction   originalCtrlPeekBufferNegative;
static CtrlBufferFunction   originalCtrlReadBufferPositive;
static CtrlBufferFunction   originalCtrlReadBufferNegative;

static unsigned int generateMask(
)
{
    unsigned int    mask = 0;

    for( int i = 0 ; i < 32 ; i++ ) {
        const unsigned int  BIT = 1 << i;
        if( sceCtrlGetButtonMask( BIT ) == 1 ) {
            mask |= BIT;
        }
    }

    return mask;
}

static void applyFromUsbData(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
    , const int     _NEGATIVE
)
{
    const int   STATE = pspSdkDisableInterrupts();

    unsigned int    buttons = currentFromUsbData.buttons;

    int k1;
    asm __volatile__ ( "move %0, $k1" : "=r"( k1 ) );
    if( k1 != 0 ) {
        buttons &= ~generateMask();
    }

    for( int i = 0 ; i < _COUNT ; i++ ) {
        SceCtrlData *   ctrlData = &( _ctrlData[ i ] );

        if( _NEGATIVE != 0 ) {
            ctrlData->Buttons &= ~buttons;
        } else {
            ctrlData->Buttons |= buttons;
        }

        ctrlData->Lx = currentFromUsbData.axisX;
        ctrlData->Ly = currentFromUsbData.axisY;
    }

    pspSdkEnableInterrupts( STATE );
}

static int hookedCtrlBuffer(
    SceCtrlData *               _ctrlData
    , const int                 _COUNT
    , const int                 _NEGATIVE
    , const CtrlBufferFunction  _ORIGINAL
)
{
    const int   COUNT = _ORIGINAL(
        _ctrlData
        , _COUNT
        , _NEGATIVE
    );
    if( COUNT <= 0 ) {
        return COUNT;
    }

    applyFromUsbData(
        _ctrlData
        , COUNT
        , _NEGATIVE
    );

    return COUNT;
}

static int hookedCtrlPeekBufferPositive(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
    , const int     _NEGATIVE
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , _NEGATIVE
        , originalCtrlPeekBufferPositive
    );
}

static int hookedCtrlPeekBufferNegative(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
    , const int     _NEGATIVE
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , _NEGATIVE
        , originalCtrlPeekBufferNegative
    );
}

static int hookedCtrlReadBufferPositive(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
    , const int     _NEGATIVE
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , _NEGATIVE
        , originalCtrlReadBufferPositive
    );
}

static int hookedCtrlReadBufferNegative(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
    , const int     _NEGATIVE
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , _NEGATIVE
        , originalCtrlReadBufferNegative
    );
}

void initializeCtrlFromUsbData(
)
{
    currentFromUsbData.value = INITIALIZE_VALUE;
}

int hookCtrlFunctions(
)
{
    HOOK_FUNCTION(
        sceCtrlPeekBufferPositive
        , hookedCtrlPeekBufferPositive
        , &originalCtrlPeekBufferPositive
    )

    HOOK_FUNCTION(
        sceCtrlPeekBufferNegative
        , hookedCtrlPeekBufferNegative
        , &originalCtrlPeekBufferNegative
    )

    HOOK_FUNCTION(
        sceCtrlReadBufferPositive
        , hookedCtrlReadBufferPositive
        , &originalCtrlReadBufferPositive
    )

    HOOK_FUNCTION(
        sceCtrlReadBufferNegative
        , hookedCtrlReadBufferNegative
        , &originalCtrlReadBufferNegative
    )

/*
    HOOK_FUNCTION(
        sceCtrlPeekLatch
        , hookedCtrlPeekLatch
        , &originalCtrlPeekLatch
    )

    HOOK_FUNCTION(
        sceCtrlReadLatch
        , hookedCtrlReadLatch
        , &originalCtrlReadLatch
    )
*/

    return 0;
}

void setCtrlFromUsbData(
    const unsigned int  _VALUE
)
{
    const int   STATE = pspSdkDisableInterrupts();

    currentFromUsbData.value = _VALUE;

    pspSdkEnableInterrupts( STATE );
}
