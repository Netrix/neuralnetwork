#pragma once

template<class Type>
struct ConstNode
{
    ConstNode(Type & value)
        : m_value(value)
    {}

private:
    Type & m_value;
};
