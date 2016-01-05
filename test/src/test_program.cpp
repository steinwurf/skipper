// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/program.hpp>

#include <gtest/gtest.h>
#include <stub/call.hpp>

#include <sstream>


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

TEST(TestProgram, void_command)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);

    stub::call<void(void)> m_print_function;
    auto print_function = [&](){m_print_function();};

    p.add_command("p", "print something", print_function);
    test_in.str("p\n p\n p\n");
    p.run(false);
    EXPECT_EQ(3U,m_print_function.calls());
    EXPECT_EQ("",test_out.str());
}

TEST(TestProgram, int_set_command)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);

    stub::call<void(int)> m_function;
    std::function<void(int)> function = [&](int value){m_function(value);};
    p.add_command<int>("a", "help", function, skipper::set<int>({0,7,42,1}));

    test_in.str("a\n 42\n a\n -10\n a\n 0\n a\n 7 a\n 11\n");
    p.run(false);
    EXPECT_EQ(3U,m_function.calls());
    EXPECT_TRUE(!!m_function.expect_calls().with(42).with(0).with(7));
}

TEST(TestProgram, float_range_command)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);

    stub::call<void(float)> m_function;
    std::function<void(float)> function = [&](float value){m_function(value);};
    p.add_command<int>("a", "help", function, skipper::range<float>(-4,7.2));

    test_in.str("a\n 42\n a\n -1\n a\n 0\n a\n 7 a\n 11\n");
    p.run(false);
    EXPECT_EQ(3U,m_function.calls());
    EXPECT_TRUE(!!m_function.expect_calls().with(-1).with(0).with(7));
}
