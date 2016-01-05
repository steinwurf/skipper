=======
skipper
=======

skipper is a small C++ library that could help you create a simple interactive
command-line like applications.

.. contents:: Table of Contents:
   :local:

Header-only
===========

The library itself is header-only so essentially to use it you just have to
clone the repository and setup the right include paths in the project where you
would like to use it.

The library uses a few c++11 features, so you need a relatively recent compiler
to use it.

Adding Commands
===============

To create a meaningfull program you need to add some commands to it.

::
    #include <skipper/program.hpp>

    skipper::program p("Some text describing what the program does");
    p.add_command<std::string>("a", "Some helpful text", some_function,
                               skipper::any<std::string>());

    return p.run();

here some_function takes a std::string as input. In the resulting executable.

* pressing 'a' and 'enter' will promt for more input in this case a string and
some_function will be called with it, provided the user managed to type a valid
string.
* pressing 'h' and 'enter' will display some helpful text, if you provided it.
* pressing 'q' and 'enter' will exit the program (p.run() will return an int).

You can also add functions that take some other input types

::
    p.add_command<int>("b", "Some helpfuller text", int_function,
                       skipper::any<int>());
    p.add_command<float>("b", "The Helpfullest text", float_function,
                       skipper::any<float>());

Or functions that take no input

::
    p.add_command("p", "this function prints something", print_function);


Validate user input
===================

Usually it is meaningful to validate the input provided by the user. To this end
three options are at your disposal any, range and set.

Any accepts any input

::
    p.add_command<std::string>("c", "text", int_function,
                               skipper::any<std::string>());

Range accepts all inputs in a specified range, here [0,10]

::
    p.add_command<int>("c", "text", int_function,
                       skipper::range<float>(0,10));

Range accepts all inputs in a specified set, here {-3,1,42}

::
    p.add_command<int>("c", "text", int_function,
                       skipper::set<int>({-3,1,42}));

You can of course also provide you own Predicate as long as you also provide an
overload for the corresponding << operator which is used to provide help output.

::

    template<typename Type>
    struct conservative
    {
        bool operator()(const Type value) const
        {
            return false;
        }

        friend std::ostream& operator<<(std::ostream& os, const conservative &c)
        {
            return os << "some friendly help text telling you no";
        }
    };

    p.add_command<std::string>("no", "this function is picky with the input",
                               picky_function, conservative<std::string>());


Custom convert of user input
============================

If your function happens to take inputs of a type which the default converter
function cannot handle you can provide your own.

::
    const Magic default_convert(std::istream& in)
    {
        Magic number = 42;
        return number;
    }

    p.add_command<Magic>("?", "Some helpful text", magic_function,
                         skipper::any<std::string>());

Provide alternative input and output
====================================

You can also provide alternative input and output streams for the program, which
can be useful for testing.

::
    std::istringstream test_in;
    std::ostringstream test_out;
    skipper::program p("test program", test_in, test_out);

    test_in.str("q\n");

    p.run(false);

    assert(test_out.str().compare("") != 0);
