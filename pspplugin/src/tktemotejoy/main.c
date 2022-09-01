#include "tktemotejoy/ctrl.h"
#include "usbasync.h"
#include "usbhostfs.h"
#include <pspkernel.h>
#include <pspusb.h>

PSP_MODULE_INFO(
    "TktemoteJoy"
    , PSP_MODULE_KERNEL
    , 1
    , 1
);

struct AsyncEndpoint    asyncEndpoint;

typedef struct
{
    _Alignas( 4 ) unsigned int magic;
    _Alignas( 4 ) unsigned int value;
} UsbAsyncData;

enum {
    JOY_MAGIC = 0x909ACCF0,
};

static int mainThread(
    SceSize     _args
    , void *    _argp
)
{
    initializeCtrlFromUsbData();

    if( hookCtrlFunctions() != 0 ) {
        sceKernelExitDeleteThread( 0 );
    }

    if( sceUsbStart(
        PSP_USBBUS_DRIVERNAME
        , 0
        , 0
    ) != 0 ) {
        return 0;
    }

    if( sceUsbStart(
        HOSTFSDRIVER_NAME
        , 0
        , 0
    ) != 0) {
        return 0;
    }

    if( sceUsbActivate( HOSTFSDRIVER_PID ) != 0 ) {
        return 0;
    }

    sceKernelDcacheWritebackInvalidateAll();
    sceKernelIcacheInvalidateAll();

    if( usbAsyncRegister(
        ASYNC_USER
        , &asyncEndpoint
    ) < 0 ) {
        sceKernelExitDeleteThread( 0 );
    }

    usbWaitForConnect();

    UsbAsyncData    usbAsyncData;

    while( 1 ) {
        const int   LENGTH = usbAsyncRead(
            ASYNC_USER
            , ( void * )&usbAsyncData
            , sizeof( usbAsyncData )
        );

        if( ( LENGTH != sizeof( usbAsyncData ) ) || ( usbAsyncData.magic != JOY_MAGIC ) ) {
            if( LENGTH < 0 ) {
                // Delay thread, necessary to ensure that the kernel can reboot :)
                sceKernelDelayThread( 250000 );
            } else {
                usbAsyncFlush( ASYNC_USER );
            }

            continue;
        }

        setCtrlFromUsbData( usbAsyncData.value );
    }

    return 0;
}

int module_start(
    SceSize     _args
    , void *    _argp
)
{
    const int   THREAD_ID = sceKernelCreateThread(
        "TktemoteJoy"
        , mainThread
        , 15
        , 0x800
        , 0
        , NULL
    );
    if( THREAD_ID >= 0 ) {
        sceKernelStartThread(
            THREAD_ID
            , _args
            , _argp
        );
    }

    return 0;
}

int module_stop(
    SceSize     _args
    , void *    _argp
)
{
    return 0;
}
