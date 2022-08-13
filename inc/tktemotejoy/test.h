#ifndef TKTEMOTEJOY_TEST_H
#define TKTEMOTEJOY_TEST_H

#include <gtest/gtest.h>

int main(
    int         _argc
    , char **   _argv
)
{
    ::testing::InitGoogleTest(
        &_argc
        , _argv
    );

    return RUN_ALL_TESTS();
}

#endif  // TKTEMOTEJOY_TEST_H
