// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <cassert>
#include <iostream>
#include <typeinfo>

namespace skipper
{

    /// validates that the provided value is within a defined range
    template<typename Type>
    struct range
    {
        range(Type lower, Type upper)
            : m_lower(lower), m_upper(upper)
        {
            assert(lower <= upper);
        }

        /// @copydoc any::operator()
        bool operator()(const Type value) const
        {
            return ((value >= m_lower) && (value <= m_upper));
        }

        /// @copydoc any::operator<<
        friend std::ostream& operator<<(std::ostream& os, const range &r)
        {
            return os << "of type " << typeid(Type).name() << " in ["
                      << r.m_lower << "," << r.m_upper << "]";
        }

    private:

        /// the lower limit in the range
        const Type m_lower;

        /// the upper limit in the range
        const Type m_upper;
    };
}
