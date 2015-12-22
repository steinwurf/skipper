// Copyright Steinwurf ApS 2015.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.


#include <skipper/some.hpp>
#include <gtest/gtest.h>

TEST(TestSome, return_value_of_some_method)
{
    skipper::some s;
    EXPECT_TRUE(s.some_method());
}
