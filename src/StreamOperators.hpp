#pragma once
#include "Utils/ArrayView.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include <vector>
#include <iostream>

inline std::ostream& operator<<(std::ostream& out, std::vector<BNN_TYPE> const& values)
{
    out << " [ ";
    for(auto a : values)
    {
        out << a << ", ";
    }
    return out << " ] ";
}

inline std::ostream& operator<<(std::ostream& out, ArrayView<BNN_TYPE const> const& values)
{
    out << " [ ";
    for(auto a : values)
    {
        out << a << ", ";
    }
    return out << " ] ";
}
