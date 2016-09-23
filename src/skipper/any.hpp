// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <iostream>
#include <typeinfo>

namespace skipper
{

    /// validates true no matter what value provided
    template<typename Type>
    struct any
    {
        /// check if a value is ok to use
        /// @param value the value to check
        /// @return wether the provided value checked
        bool operator()(const Type value) const
        {
            (void) value;
            return true;
        }

        /// print help text by overloading the << operator
        /// @param os an output stream
        /// @param s a set
        /// @return friendly help stream
        friend std::ostream& operator<<(std::ostream& os, const any& a)
        {
            (void) a;
            return os << "of type " << typeid(Type).name() << " of any value";
        }
    };
}
