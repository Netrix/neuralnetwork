#pragma once
#include "ArrayView.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

namespace Details
{

template<class FirstContainer, class SecondContainer, class Functor>
auto getBinaryResult(FirstContainer const& firstContainer, SecondContainer const& secondContainer, Functor f)
{
    using FIRST_CONTAINER_VALUE_TYPE = typename std::remove_cv<typename FirstContainer::value_type>::type;
    using SECOND_CONTAINER_VALUE_TYPE = typename std::remove_cv<typename SecondContainer::value_type>::type;
    static_assert(std::is_same<FIRST_CONTAINER_VALUE_TYPE, SECOND_CONTAINER_VALUE_TYPE>::value, "Given containers must have the same type!");

    std::vector<FIRST_CONTAINER_VALUE_TYPE> results;
    results.reserve(firstContainer.size());

    std::transform(std::begin(firstContainer), std::end(firstContainer), std::begin(secondContainer), std::back_inserter(results), f);
    return results;
}

template<class FirstContainer, class SecondContainer, class Functor>
auto assignTransform(FirstContainer & firstContainer, SecondContainer const& secondContainer, Functor f)
{
    using FIRST_CONTAINER_VALUE_TYPE = typename std::remove_cv<typename FirstContainer::value_type>::type;
    using SECOND_CONTAINER_VALUE_TYPE = typename std::remove_cv<typename SecondContainer::value_type>::type;
    static_assert(std::is_same<FIRST_CONTAINER_VALUE_TYPE, SECOND_CONTAINER_VALUE_TYPE>::value, "Given containers must have the same type!");

    std::transform(std::begin(firstContainer), std::end(firstContainer), std::begin(secondContainer), std::begin(firstContainer), f);
}

} // namespace


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

    template<class OtherType>
    MathVectorAdapter<Type> operator-(MathVectorAdapter<OtherType> const& ref) const
    {
        return Details::getBinaryResult(m_values, ref.m_values, [](auto a, auto b)
        {
            return a - b;
        });
    }

    template<class OtherType>
    MathVectorAdapter<Type> operator*(MathVectorAdapter<OtherType> const& ref) const
    {
        return Details::getBinaryResult(m_values, ref.m_values, [](auto a, auto b)
        {
            return a * b;
        });
    }

    template<class OtherType>
    MathVectorAdapter<Type>& operator+=(MathVectorAdapter<OtherType> const& ref)
    {
        Details::assignTransform(m_values, ref.m_values, [](auto a, auto b)
        {
            return a + b;
        });
        return *this;
    }

    template<class OtherType>
    MathVectorAdapter<Type>& operator/=(MathVectorAdapter<OtherType> const& ref)
    {
        Details::assignTransform(m_values, ref.m_values, [](auto a, auto b)
        {
            return a / b;
        });
        return *this;
    }

    template<class OtherType>
    MathVectorAdapter<Type>& operator*=(MathVectorAdapter<OtherType> const& ref)
    {
        Details::assignTransform(m_values, ref.m_values, [](auto a, auto b)
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
    std::vector<Type> m_values;
};

template<class Type>
auto make_math_adapter(Type const& args)
{
    return MathVectorAdapter<typename std::remove_cv<typename Type::value_type>::type>(args);
}

