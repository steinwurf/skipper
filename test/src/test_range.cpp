// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/range.hpp>

#include <gtest/gtest.h>

TEST(range, basic)
{
    skipper::range<float> r(-3.F, 5.0F);
    EXPECT_TRUE(r(-3));
    EXPECT_TRUE(r(0));
    EXPECT_TRUE(r(5));
    EXPECT_FALSE(r(6));
}
