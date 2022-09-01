#ifndef CTRL_SRC_H
#define CTRL_SRC_H

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
);

enum {
    INITIALIZE_VALUE = 0x80800000,
};

static FromUsbData  currentFromUsbData;

static CtrlBufferFunction   originalCtrlPeekBufferPositive;
static CtrlBufferFunction   originalCtrlPeekBufferNegative;
#ifndef FOR_POPS
static CtrlBufferFunction   originalCtrlReadBufferPositive;
static CtrlBufferFunction   originalCtrlReadBufferNegative;
#endif  // FOR_POPS

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

#ifdef  ENABLE_PSP_ANALOG_PAD
static unsigned char calcAxisDistance(
    const unsigned char _AXIS
)
{
    char    distance = _AXIS ^ 0x80;

    if( distance < 0 ) {
        distance *= -1;
    }

    return distance;
}

static unsigned char getMaxAxis(
    const unsigned char     _AXIS1
    , const unsigned char   _AXIS2
)
{
    const unsigned char AXIS_DISTANCE1 = calcAxisDistance( _AXIS1 );
    const unsigned char AXIS_DISTANCE2 = calcAxisDistance( _AXIS2 );

    return AXIS_DISTANCE1 > AXIS_DISTANCE2 ? _AXIS1 : _AXIS2;
}
#endif  // ENABLE_PSP_ANALOG_PAD

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

#ifdef  ENABLE_PSP_ANALOG_PAD
        ctrlData->Lx = getMaxAxis(
            ctrlData->Lx
            , currentFromUsbData.axisX
        );
        ctrlData->Ly = getMaxAxis(
            ctrlData->Ly
            , currentFromUsbData.axisY
        );
#else   // ENABLE_PSP_ANALOG_PAD
        ctrlData->Lx = currentFromUsbData.axisX;
        ctrlData->Ly = currentFromUsbData.axisY;
#endif  // ENABLE_PSP_ANALOG_PAD
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
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , 0
        , originalCtrlPeekBufferPositive
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

#ifndef FOR_POPS
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

static int hookedCtrlReadBufferNegative(
    SceCtrlData *   _ctrlData
    , const int     _COUNT
)
{
    return hookedCtrlBuffer(
        _ctrlData
        , _COUNT
        , 1
        , originalCtrlReadBufferNegative
    );
}
#endif  // FOR_POPS

void initializeCtrlFromUsbData(
)
{
    currentFromUsbData.value = INITIALIZE_VALUE;
}

int hookCtrlFunctions(
)
{
    // PSメニューでのボタン検知
    HOOK_FUNCTION(
        sceCtrlPeekBufferPositive
        , hookedCtrlPeekBufferPositive
        , &originalCtrlPeekBufferPositive
    )

    // PS1ゲームでのボタン検知
    HOOK_FUNCTION(
        sceCtrlPeekBufferNegative
        , hookedCtrlPeekBufferNegative
        , &originalCtrlPeekBufferNegative
    )

#ifndef FOR_POPS
    // 3つ以上の関数をフックするとPS1のゲームでボタンが反応しなくなる
    // 理由は不明

    // シェルやPSPゲームでのボタン検知
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
#endif  // FOR_POPS

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

#endif  // CTRL_SRC_H
