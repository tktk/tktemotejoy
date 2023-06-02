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

typedef struct {
    struct SceModule2   *next;
    unsigned short      attribute;
    unsigned char       version[2];
    char                modname[27];
    char                terminal;
    unsigned int        unknown1;
    unsigned int        unknown2;
    SceUID              modid;
    unsigned int        unknown3[2];
    u32         mpid_text;  // 0x38
    u32         mpid_data; // 0x3C
    void *              ent_top;
    unsigned int        ent_size;
    void *              stub_top;
    unsigned int        stub_size;
    unsigned int        unknown4[5];
    unsigned int        entry_addr;
    unsigned int        gp_value;
    unsigned int        text_addr;
    unsigned int        text_size;
    unsigned int        data_size;
    unsigned int        bss_size;
    unsigned int        nsegment;
    unsigned int        segmentaddr[4];
    unsigned int        segmentsize[4];
} SceModule2;

#define MAKE_JUMP(a, f) _sw(0x08000000 | (((u32)(f) & 0x0FFFFFFC) >> 2), a);

#define HIJACK_FUNCTION( a, f, ptr ) { \
    u32 func = a; \
    static u32 patch_buffer[3]; \
    _sw(_lw(func), (u32)patch_buffer); \
    _sw(_lw(func + 4), (u32)patch_buffer + 8); \
    MAKE_JUMP((u32)patch_buffer + 4, func + 8); \
    _sw(0x08000000 | (((u32)(f) >> 2) & 0x03FFFFFF), func); \
    _sw(0, func + 4); \
    ptr = (void *)patch_buffer; \
}

int hookFunction2(
    const char *    _MODULE_NAME
    , u32           _ADDRESS
    , void *        _hookFunc
    , void **       _orgFunc
)
{
    SceModule2 *mod = ( SceModule2 * )sceKernelFindModuleByName( _MODULE_NAME );

    int i;
    for( i = 0 ; i < mod->text_size ; i += 4 ) {
        u32 addr = mod->text_addr + i;

        if( _lw( addr ) == _ADDRESS ) {
            HIJACK_FUNCTION(
                addr - 0x1C
                , _hookFunc
                , *_orgFunc
            );

            break;
        }
    }

    if( i >= mod->text_size ) {
        return 1;
    }

    return 0;
}
