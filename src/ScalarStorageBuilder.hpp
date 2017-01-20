#pragma once
#include "ScalarStorage.hpp"
#include <vector>
#include <memory>

template<class Type, class Tag>
struct ScalarStorageBuilder
{
    ScalarStorageBuilder(std::size_t numConsts)
        : m_storage(numConsts)
    {}

    Type & getSingleValueRef()
    {
        return m_storage[m_current++];
    }

    auto build()
    {
        return std::make_unique<ScalarStorage<Type, Tag>>(std::move(m_storage));
    }

private:
    std::size_t m_current{};
    std::vector<Type> m_storage;
};
