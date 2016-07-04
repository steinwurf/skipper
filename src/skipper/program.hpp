// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include "any.hpp"
#include "range.hpp"
#include "set.hpp"

#include <iostream>
#include <functional>
#include <map>
#include <sstream>
#include <tuple>

namespace skipper
{
    /// generic converter
    template<typename Type>
    const Type default_convert(std::istream& in)
    {
        Type value;
        if(!(in >> value))
        {
            // reset the input stream error state and read all inputs
            in.clear();
            std::string temp;
            in >> temp;

            throw std::string("Could not convert the input");
        }

        return value;
    }

    /// defines a number of commands that can be executed by the user making
    /// various function calls optinally providing an argument
    class program
    {

    public:

        /// the command type
        using command_type = std::function<void()>;

        /// storage for a command
        using command_storage = std::tuple<command_type, std::string>;

        /// @param description
        /// @param in the input stream to use
        /// @param out the output stream to use
        program(std::string description,
                std::istream& in = std::cin,
                std::ostream& out = std::cout)
            : m_description(description), m_in(in), m_out(out)
        {
            add_command("h", "print this help", [&](){m_out << *this;});
        }

        /// add a command to the program
        /// @param key what to press to pick the command
        /// @param description help text for the command
        /// @param call the function that will be called by the command
        void add_command(const std::string key,
                         std::string description,
                         command_type call)
        {
            assert(!m_commands.count(key));

            m_commands[key] = std::make_tuple(call, description);
        }

        /// @copydoc add_command
        /// @param validate Predicate that validates the input for the command
        /// @param convert function that converts the input string
        template<typename Type, typename Predicate = any<Type>>
        void add_command(const std::string key,
                         std::string description,
                         const std::function<void(const Type)>& call,
                         const Predicate& validate = any<Type>(),
                         std::function<const Type(std::istream&)> convert =
                            default_convert<Type>)
        {
            assert(!m_commands.count(key) && "Duplicated command");

            auto set_command = [=]()
            {
                Type value;
                try
                {
                    value = convert(m_in);
                }
                catch (std::string str)
                {
                    m_out << str << std::endl;
                    return;
                }

                if (validate(value))
                    call(value);
                else
                    m_out << "Invalid input, press 'h' for help" << std::endl;
            };

            std::ostringstream help;
            help << description << ", " << validate;
            add_command(key, description, set_command);
        }

        /// run the program
        int run()
        {
            if (m_print_help)
                m_out << *this;

            std::string in_key;

            m_out << m_ready_indicator;
            while (m_in >> in_key)
            {
                if (in_key == m_exit_key)
                    return 0;

                if (m_commands.count(in_key))
                    std::get<0>(m_commands[in_key])();
                else
                    m_out << "Invalid command, press 'h' for help" << std::endl;

                m_out << m_ready_indicator;
            }
            return 0;
        }

        /// Set wether help should be printed on run
        /// @param help_on print help at run
        void set_print_help(bool help_on)
        {
            m_print_help = help_on;
        }

        /// set the ready indicator, use "" for no indicator
        /// @param indicator the ready indicator
        void set_ready_indicator(const std::string& indicator)
        {
            m_ready_indicator = indicator;
        }

        /// Set the quit / escape key
        /// @param exit_key the key to exit the program
        void set_exit_key(const std::string& exit_key)
        {
            m_exit_key = exit_key;
        }

    private:

        /// print help text by overloading the << operator
        /// @param os an output stream
        /// @param s a set
        /// @return friendly help stream
        friend std::ostream& operator<<(std::ostream& os, const program &p)
        {
            os << std::endl << p.m_description << std::endl << std::endl
               << "The following commands are accepted:" << std::endl;

            for(auto i = p.m_commands.begin(); i != p.m_commands.end(); i++)
                os << i->first << " " << std::get<1>(i->second) << std::endl;

            os << p.m_exit_key << " exit the program" << std::endl << std::endl;

            return os;
        }

    private:

        /// help text for the program
        std::string m_description;

        /// the input stream used
        std::istream& m_in;

        /// the output stream used
        std::ostream& m_out;

        /// the parameters support by the program
        std::map<std::string, command_storage> m_commands;


        /// Print help on run
        bool m_print_help = true;

        /// Ready indicator
        std::string m_ready_indicator = "> ";

        /// the string that terminates the program
        std::string m_exit_key = "q";
    };
}
