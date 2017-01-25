#pragma once
#include "ArrayView.hpp"
#include <vector>
#include <numeric>

template<class Type>
struct MathVectorAdapter
{
    template<class Container>
    MathVectorAdapter(Container const& c)
        : m_values(std::begin(c), std::end(c))
    {}

    MathVectorAdapter(std::size_t numItems)
        : m_values(numItems)
    {}

    MathVectorAdapter<Type> operator-(MathVectorAdapter<Type> const& ref)
    {
        return getBinaryResult(ref, [](auto a, auto b)
        {
            return a - b;
        });
    }

    MathVectorAdapter<Type> operator*(MathVectorAdapter<Type> const& ref)
    {
        return getBinaryResult(ref, [](auto a, auto b)
        {
            return a * b;
        });
    }

    MathVectorAdapter<Type>& operator+=(MathVectorAdapter<Type> const& ref)
    {
        assignTransform(ref, [](auto a, auto b)
        {
            return a + b;
        });
        return *this;
    }

    MathVectorAdapter<Type>& operator/=(MathVectorAdapter<Type> const& ref)
    {
        assignTransform(ref, [](auto a, auto b)
        {
            return a / b;
        });
        return *this;
    }

    MathVectorAdapter<Type>& operator*=(MathVectorAdapter<Type> const& ref)
    {
        assignTransform(ref, [](auto a, auto b)
        {
            return a + b;
        });
        return *this;
    }

    MathVectorAdapter<Type>& operator*=(Type scalar)
    {
        for(auto& a : m_values)
        {
            a *= scalar;
        }
        return *this;
    }

    operator ArrayView<Type const>() const
    {
        return m_values;
    }

    MathVectorAdapter<Type>& operator/=(Type scalar)
    {
        for(auto& a : m_values)
        {
            a /= scalar;
        }
        return *this;
    }

    operator ArrayView<Type>()
    {
        return m_values;
    }

    auto sum() const
    {
        return std::accumulate(std::begin(m_values), std::end(m_values), Type{});
    }

    template<class Generator>
    void fillWithGenerator(Generator && p_generator)
    {
        for(auto & a : m_values)
        {
            a = p_generator();
        }
    }

private:
    template<class Functor>
    auto getBinaryResult(MathVectorAdapter<Type> const& ref, Functor f)
    {
        std::vector<Type> results;
        results.reserve(m_values.size());

        std::transform(std::begin(m_values), std::end(m_values), std::begin(ref.m_values), std::back_inserter(results), f);
        return MathVectorAdapter<Type>(results);
    }

    template<class Functor>
    auto assignTransform(MathVectorAdapter<Type> const& ref, Functor f)
    {
        std::transform(std::begin(m_values), std::end(m_values), std::begin(ref.m_values), std::begin(m_values), f);
    }

private:
    std::vector<Type> m_values;
};

template<class Type>
auto make_math_adapter(Type const& args)
{
    return MathVectorAdapter<typename std::remove_cv<typename Type::value_type>::type>(args);
}

