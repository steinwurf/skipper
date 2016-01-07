// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/any.hpp>

#include <gtest/gtest.h>

TEST(any, basic)
{
    skipper::any<int> a;
    EXPECT_TRUE(a(-1));
    EXPECT_TRUE(a(0));
    EXPECT_TRUE(a(1));
}
