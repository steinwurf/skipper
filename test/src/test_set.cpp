// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/set.hpp>

#include <gtest/gtest.h>

TEST(set, basic)
{
    {
        skipper::set<int> s({1,2,4,16});
        EXPECT_TRUE(s(1));
        EXPECT_TRUE(s(2));
        EXPECT_TRUE(s(4));
        EXPECT_TRUE(s(16));
        EXPECT_FALSE(s(0));
        EXPECT_FALSE(s(3));
    }
    {
        skipper::set<std::string> s({"stein","wurf"});
        EXPECT_TRUE(s("stein"));
        EXPECT_TRUE(s("wurf"));
        EXPECT_FALSE(s("out"));
        EXPECT_FALSE(s("0"));
    }
}
