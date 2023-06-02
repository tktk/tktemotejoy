#include "tktemotejoy/ctrl.h"
#include "tktemotejoy/hook.h"
#include <pspctrl.h>
#include <pspctrl_kernel.h>
#include <pspkernel.h>

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
);

enum {
    INITIALIZE_VALUE = 0x80800000,
};

static FromUsbData      currentFromUsbData;
static unsigned char    enabled = 0;

static CtrlBufferFunction   originalCtrlReadBufferPositive;
static CtrlBufferFunction   originalCtrlPeekBufferNegative;

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
    if( enabled == 0 ) {
        return;
    }

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

static int hookedCtrlReadBufferPositive(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , 0
        , originalCtrlReadBufferPositive
    );
}

static int hookedCtrlPeekBufferNegative(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , 1
        , originalCtrlPeekBufferNegative
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
#define HOOK_FUNCTION( \
        _JUMP \
        , _HOOKED \
        , _ORIGINAL \
    ) if( hookFunction( \
        _JUMP \
        , _HOOKED \
        , ( void ** )_ORIGINAL \
    ) != 0 ) { \
        return 1; \
    }

#define HOOK_FUNCTION2( \
        _MODULE_NAME \
        , _ADDRESS \
        , _HOOKED \
        , _ORIGINAL \
    ) if( hookFunction2( \
        _MODULE_NAME \
        , _ADDRESS \
        , _HOOKED \
        , ( void ** )_ORIGINAL \
    ) != 0 ) { \
        return 1; \
    }

    // シェル、PSPゲーム、PSメニューでのボタン検知
    HOOK_FUNCTION2(
        "sceController_Service"
        , 0x35030104
        , hookedCtrlReadBufferPositive
        , &originalCtrlReadBufferPositive
    )

    // PS1ゲームでのボタン検知
    HOOK_FUNCTION(
        sceCtrlPeekBufferNegative
        , hookedCtrlPeekBufferNegative
        , &originalCtrlPeekBufferNegative
    )

    return 0;

#undef  HOOK_FUNCTION
#undef  HOOK_FUNCTION2
}

void setCtrlFromUsbData(
    const unsigned int  _VALUE
)
{
    currentFromUsbData.value = _VALUE;
    enabled = 1;
}

void disableCtrlFromUsbData(
)
{
    enabled = 0;
}
