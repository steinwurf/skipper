// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/program.hpp>

#include <gtest/gtest.h>
#include <stub/call.hpp>

#include <sstream>

TEST(test_program, initialize)
{
    skipper::program p("dummy help text");
}

TEST(test_program, void_command)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);
    p.set_print_help(false);
    p.set_ready_indicator("");

    stub::call<void(void)> m_print_function;
    auto print_function = [&](){m_print_function();};

    p.add_command("p", "print something", print_function);
    test_in.str("p\n p\n p\n q\n");
    p.run();
    EXPECT_EQ(3U, m_print_function.calls());
    EXPECT_EQ("", test_out.str());
}

TEST(test_program, int_set_command)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);
    p.set_print_help(false);
    p.set_ready_indicator("");

    stub::call<void(int)> m_function;
    std::function<void(int)> function = [&](int value){m_function(value);};
    p.add_command<int>("a", "help", function, skipper::set<int>({0,7,42,1}));

    test_in.str("a\n 42\n a\n -10\n a\n 0\n a\n 7 a\n 11\n");
    p.run();
    EXPECT_EQ(3U, m_function.calls());
    EXPECT_TRUE(m_function.expect_calls().with(42).with(0).with(7).to_bool());
}

TEST(test_program, string_any_command)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);
    p.set_print_help(false);
    p.set_ready_indicator("");

    stub::call<void(std::string)> m_function;
    std::function<void(std::string)> function =
        [&](std::string value){m_function(value);};
    p.add_command<std::string>("a", "help", function);

    test_in.str("a\n hello\n a\n world\n");
    p.run();
    EXPECT_EQ(2U, m_function.calls());
    EXPECT_TRUE(
        m_function.expect_calls().with("hello").with("world").to_bool());
}

TEST(test_program, float_range_command)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);
    p.set_print_help(false);
    p.set_ready_indicator("");

    stub::call<void(float)> m_function;
    std::function<void(float)> function = [&](float value){m_function(value);};
    p.add_command<float>("a", "help", function,
        skipper::range<float>(-4.0F, 7.2F));

    test_in.str("a\n 42\n a\n -1\n a\n 0\n a\n 7\n a\n 11\n");
    p.run();
    EXPECT_EQ(3U, m_function.calls());
    EXPECT_TRUE(m_function.expect_calls().with(-1).with(0).with(7).to_bool());
}

TEST(test_program, trigger_errors)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);
    p.set_print_help(false);
    p.set_ready_indicator("");

    stub::call<void(int)> m_function;
    std::function<void(int)> function = [&](int value){m_function(value);};
    p.add_command<int>("a", "help", function, skipper::range<int>(0, 10));

    test_in.str("wrong key\n a\n wrong input\n q\n");

    p.run();
    EXPECT_NE("", test_out.str());
}

TEST(test_program, print_help_on)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);
    p.set_ready_indicator("");

    p.run();
    EXPECT_EQ("\ndummy help text\n\nThe following commands are accepted:\n"
              "h print this help\nq exit the program\n\n", test_out.str());
}

TEST(test_program, custom_ready_indicator)
{
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("dummy help text", test_in, test_out);
    p.set_print_help(false);
    p.set_ready_indicator("? ");

    p.run();
    EXPECT_EQ("? ", test_out.str());
}
