#pragma once
#include <vector>
#include "Utils/ArrayView.hpp"

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

    ArrayView<Type const> getValues() const
    {
        return m_storage;
    }

    ArrayView<Type> getValues()
    {
        return m_storage;
    }

    template<class Generator>
    void setValuesByGenerator(Generator && p_generator)
    {
        for(auto & a : m_storage)
        {
            a = p_generator();
        }
    }

private:
    std::vector<Type> m_storage;
};
