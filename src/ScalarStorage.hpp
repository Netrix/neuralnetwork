#pragma once
#include <vector>
#include "ArrayView.hpp"

template<class Type, class Tag>
struct ScalarStorage
{
    ScalarStorage(std::vector<Type> && storage)
        : m_storage(std::move(storage))
    {}

    void setValues(ArrayView<Type const> values)
    {
        assert(m_storage.size() == values.size());
        std::copy(std::begin(values), std::end(values), std::begin(m_storage));
    }

private:
    std::vector<Type> m_storage;
};
