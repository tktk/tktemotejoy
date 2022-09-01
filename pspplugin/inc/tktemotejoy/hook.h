#ifndef HOOK_H
#define HOOK_H

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

int hookFunction(
    void *
    , void *
    , void **
);

#endif  // HOOK_H
