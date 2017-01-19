#pragma once

#include "ComputationNode.hpp"

template<class Type>
struct ConstNode : ComputationNode
{
    ConstNode(Type & value)
        : m_value(value)
    {}

private:
    Type & m_value;
};
