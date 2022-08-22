#ifndef TKTEMOTEJOY_DESCRIPTORCLOSER_H
#define TKTEMOTEJOY_DESCRIPTORCLOSER_H

#include <memory>

struct CloseDescriptor
{
    void operator()(
        int *
    ) const;
};

using DescriptorCloser = std::unique_ptr<
    int
    , CloseDescriptor
>;

#endif  // TKTEMOTEJOY_DESCRIPTORCLOSER_H
