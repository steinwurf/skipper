// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/program.hpp>

int main()
{
    // dummy functions called by the program
    auto function_str = [&](std::string s){std::cout << "called with: " << s;};
    auto function_int = [&](int i){std::cout << "called with: " << i;};
    auto function_float = [&](float f){std::cout << "called with: " << f;};
    auto print_function = [&](){std::cout << "prints some useful value";};

    // create a program with some help text
    skipper::program p("This is a program for demonstration purposes");

    // add a command that takes any string as input
    p.add_command<std::string>("a", "some help text for a", function_str,
                               skipper::any<std::string>());

    // add a command that takes a float in a certain range as intput
    p.add_command<float>("b", "some help text for b", function_float,
                         skipper::range<float>(0,5));

    // add a command that takes an integer in a certain set as intput
    p.add_command<int>("c", "some help text for c", function_int,
                       skipper::set<int>({2,4,8,16}));

    // add a command that prints something useful
    p.add_command("p", "print something", print_function);

    // run the program
    return p.run();
}
