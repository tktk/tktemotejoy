#include "tktemotejoy/ctrl.h"
#include "tktusbmanager/tktusbmanager.h"
#include <pspkernel.h>
#include <psputils.h>
#include <string.h>

PSP_MODULE_INFO(
    "TktemoteJoy"
    , PSP_MODULE_KERNEL
    , 1
    , 1
);

#define ENDPOINT_NAME "tktemotejoy"

enum {
    RETRY_DELAY_USECONDS = 3000000,

    INPUT_DATA_SIZE = sizeof( int ),

    BUFFER_SIZE = 1024,
    BUFFER_COUNT = BUFFER_SIZE / INPUT_DATA_SIZE,
    BUFFER_BLOCK_SIZE = ( BUFFER_SIZE + 63 ) & ~63,
};

static TktUsbEndpointR *    endpointR = NULL;

static int mainThread(
    SceSize     _args
    , void *    _argp
)
{
    initializeCtrlFromUsbData();

    if( hookCtrlFunctions() != 0 ) {
        sceKernelExitDeleteThread( 0 );
    }

    int     buffer[ BUFFER_COUNT ] __attribute__( ( aligned( 64 ) ) );
    size_t  fragmentSize = 0;

    while( 1 ) {
        const int   READ_SIZE = tktUsbRead(
            endpointR
            , ( ( char * )buffer ) + fragmentSize
            , BUFFER_SIZE - fragmentSize
        );
        if( READ_SIZE <= 0 ) {
            fragmentSize = 0;

            disableCtrlFromUsbData();

            sceKernelDelayThread( RETRY_DELAY_USECONDS );

            continue;
        }

        const int   TOTAL_READ_SIZE = READ_SIZE + fragmentSize;
        if( TOTAL_READ_SIZE < INPUT_DATA_SIZE ) {
            fragmentSize = TOTAL_READ_SIZE;

            continue;
        }

        sceKernelDcacheInvalidateRange(
            buffer
            , BUFFER_BLOCK_SIZE
        );

        const int   INPUT_DATA_COUNT = TOTAL_READ_SIZE / INPUT_DATA_SIZE;
        const int   LATEST_INPUT_DATA_INDEX = INPUT_DATA_COUNT - 1;
        const int   LATEST_INPUT_DATA = buffer[ LATEST_INPUT_DATA_INDEX ];

        setCtrlFromUsbData( LATEST_INPUT_DATA );

        fragmentSize = TOTAL_READ_SIZE - INPUT_DATA_COUNT * INPUT_DATA_SIZE;

        if( fragmentSize > 0 ) {
            memcpy(
                buffer
                , buffer + INPUT_DATA_COUNT
                , fragmentSize
            );
        }
    }

    return 0;
}

int module_start(
    SceSize     _args
    , void *    _argp
)
{
    endpointR = tktUsbGetEndpointR(
        ENDPOINT_NAME
        , sizeof( ENDPOINT_NAME ) - 1
    );
    if( endpointR == NULL ) {
        return 0;
    }

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
