#ifndef HOOK_H
#define HOOK_H

#include <pspkernel.h>

int hookFunction(
    void *
    , void *
    , void **
);

int hookFunction2(
    const char *
    , u32
    , void *
    , void **
);

#endif  // HOOK_H
