#pragma once
#include <vector>

template<class Type, class Tag>
struct ScalarStorage
{
    ScalarStorage(std::vector<Type> && storage)
        : m_storage(std::move(storage))
    {}

private:
    std::vector<Type> m_storage;
};
