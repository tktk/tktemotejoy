#include "tktemotejoy/hook.h"
#include <pspkernel.h>

static inline unsigned int getJumpTarget(
    const unsigned int  _JUMP
)
{
    return 0x80000000 | ( ( _JUMP  & 0x03FFFFFF ) << 2 );
}

static inline int checkInst(
    const unsigned int  _INST
)
{
    if( ( _INST & ~0x03FFFFFF ) != 0x0C000000 ) {
        return 1;
    } else {
        return 0;
    }
}

int hookFunction(
    void *      _jump
    , void *    _hookFunc
    , void **   _orgFunc
)
{
    unsigned int    inst;

    unsigned int    target = getJumpTarget( *( unsigned int * )_jump );
    while( 1 ) {
        inst = _lw( target + 4 );

        if( checkInst( inst ) == 0 ) {
            break;
        }

        target += 4;
    }

    if( checkInst( inst ) != 0 ) {
        return 1;
    }

    *_orgFunc = ( void * )getJumpTarget( inst );

    unsigned int    func = ( unsigned int )_hookFunc;
    func = ( func & 0x0FFFFFFF ) >> 2;
    _sw(
        0x0C000000 | func
        , target + 4
    );

    return 0;
}
