// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/program.hpp>
#include <gtest/gtest.h>

TEST(TestProgram, any)
{
    skipper::any<int> a;
    EXPECT_TRUE(a(-1));
    EXPECT_TRUE(a(0));
    EXPECT_TRUE(a(1));
}

TEST(TestProgram, range)
{
    skipper::range<float> r(-3,5);
    EXPECT_TRUE(r(-3));
    EXPECT_TRUE(r(0));
    EXPECT_TRUE(r(5));
    EXPECT_FALSE(r(6));
}

TEST(TestProgram, set)
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

TEST(TestProgram, initialize)
{
    skipper::program p("dummy help text");
}
