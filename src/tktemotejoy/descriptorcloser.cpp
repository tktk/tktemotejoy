#include "tktemotejoy/descriptorcloser.h"
#include <unistd.h>

void CloseDescriptor::operator()(
    int *   _descriptorPtr
) const
{
    close( *_descriptorPtr );
}
