// Copyright Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>

namespace skipper
{

    /// validates that the provided value is a set
    template<typename Type>
    struct set
    {
        set(const std::initializer_list<Type> values) :
            m_values(values)
        {}

        /// @copydoc any::operator()
        bool operator()(Type value) const
        {
            return (std::find(m_values.begin(), m_values.end(), value) !=
                    m_values.end());
        }

        /// @copydoc any::operator<<
        friend std::ostream& operator<<(std::ostream& os, const set& s)
        {
            os << "of type " << typeid(Type).name() << " in {";
            for (auto i = s.m_values.begin(); i != s.m_values.end(); i++)
            {
                if (i != s.m_values.begin())
                    os << ",";
                os << *i;
            }
            return os << "}";
        }

    private:

        /// the values in the set
        const std::vector<Type> m_values;
    };
}
