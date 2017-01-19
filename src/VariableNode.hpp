#pragma once

#include "ComputationNode.hpp"

template<class Type>
struct VariableNode : ComputationNode
{
    VariableNode(Type & value)
        : m_value(value)
    {}

private:
    Type & m_value;
};

// TODO this can be common with ConstNode, differ by tag
