#include "tktemotejoy/descriptorcloser.h"
#include <unistd.h>

namespace tktemotejoy {
    void CloseDescriptor::operator()(
        int *   _descriptorPtr
    ) const
    {
        close( *_descriptorPtr );
    }
}
