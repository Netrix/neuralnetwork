#pragma once

template<class Type>
struct VariableNode
{
    VariableNode(Type & value)
        : m_value(value)
    {}

private:
    Type & m_value;
};
