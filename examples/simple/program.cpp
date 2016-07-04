// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <skipper/program.hpp>
#include <tuple>

int main()
{
    // dummy functions called by the program
    auto function_str =
        [](std::string s){std::cout << "called with: " << s << std::endl;};

    auto function_int =
        [](int i){std::cout << "called with: " << i << std::endl;};

    auto function_float =
        [](float f){std::cout << "called with: " << f << std::endl;};

    auto print_function =
        [](){std::cout << "prints some useful value" << std::endl;};

    using tuple_type = std::tuple<std::string, int>;

    auto function_str_int_tuple = [](tuple_type t)
    {
        (void)t;
        std::cout << "called with: "
                  << std::get<0>(t) << ", " << std::get<1>(t) << std::endl;
    };

    auto tuple_convert = [](std::istream& in)
    {

        auto v1 = skipper::default_convert<
            typename std::tuple_element<0, tuple_type>::type>(in);
        auto v2 = skipper::default_convert<
            typename std::tuple_element<1, tuple_type>::type>(in);

        return std::make_tuple(v1, v2);
    };

    // create a program with some help text
    skipper::program p("This is a program for demonstration purposes");

    // add a command that takes any string as input
    p.add_command<std::string>("a", "some help text for a", function_str);

    // add a command that takes a float in a certain range as intput
    p.add_command<float>("b", "some help text for b", function_float,
                         skipper::range<float>(0, 5));

    // add a command that takes an integer in a certain set as intput
    p.add_command<int>("c", "some help text for c", function_int,
                       skipper::set<int>({2, 4, 8, 16}));

    // add a command that takes any string followed by any int as input
    p.add_command<tuple_type>("d", "some help text for d",
        function_str_int_tuple, skipper::any<tuple_type>(),
        tuple_convert);

    // add a command that prints something useful
    p.add_command("p", "print something", print_function);

    p.set_ready_indicator("# ");

    p.set_print_help(true);

    // run the program
    return p.run();
}
