#pragma once
#include "Utils/ArrayView.hpp"
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


template<class Sequence>
struct MathSequenceAdapter
{
    using value_type = typename Sequence::value_type;

    template<class... Args>
    MathSequenceAdapter(Args &&... args)
        : m_values(std::forward<Args>(args)...)
    {
    }

    template<class FirstType, class SecondType>
    friend MathSequenceAdapter<FirstType> operator-(MathSequenceAdapter<FirstType> const& lhs, MathSequenceAdapter<SecondType> const& rhs);

    template<class FirstType, class SecondType>
    friend MathSequenceAdapter<FirstType> operator*(MathSequenceAdapter<FirstType> const& lhs, MathSequenceAdapter<SecondType> const& rhs);

    template<class FirstType, class SecondType>
    friend MathSequenceAdapter<FirstType>& operator+=(MathSequenceAdapter<FirstType> & lhs, MathSequenceAdapter<SecondType> const& rhs);

    template<class FirstType, class SecondType>
    friend MathSequenceAdapter<FirstType>& operator/=(MathSequenceAdapter<FirstType> & lhs, MathSequenceAdapter<SecondType> const& rhs);

    template<class FirstType, class SecondType>
    friend MathSequenceAdapter<FirstType>& operator*=(MathSequenceAdapter<FirstType> & lhs, MathSequenceAdapter<SecondType> const& rhs);

    template<class FirstType, class SecondType>
    friend MathSequenceAdapter<FirstType>& operator*=(MathSequenceAdapter<FirstType> & lhs, SecondType scalar);

    template<class FirstType, class SecondType>
    friend MathSequenceAdapter<FirstType>& operator/=(MathSequenceAdapter<FirstType> & lhs, SecondType scalar);


    operator ArrayView<value_type const>() const
    {
        return m_values;
    }

    auto sum() const
    {
        return std::accumulate(std::begin(m_values), std::end(m_values), value_type{});
    }

    template<class Generator>
    void fillWithGenerator(Generator && p_generator)
    {
        for(auto & a : m_values)
        {
            a = p_generator();
        }
    }

protected:
    Sequence m_values;
};


template<class FirstType, class SecondType>
MathSequenceAdapter<FirstType> operator-(MathSequenceAdapter<FirstType> const& lhs, MathSequenceAdapter<SecondType> const& rhs)
{
    return Details::getBinaryResult(lhs.m_values, rhs.m_values, [](auto a, auto b)
    {
        return a - b;
    });
}

template<class FirstType, class SecondType>
MathSequenceAdapter<FirstType> operator*(MathSequenceAdapter<FirstType> const& lhs, MathSequenceAdapter<SecondType> const& rhs)
{
    return Details::getBinaryResult(lhs.m_values, rhs.m_values, [](auto a, auto b)
    {
        return a * b;
    });
}

template<class FirstType, class SecondType>
MathSequenceAdapter<FirstType>& operator+=(MathSequenceAdapter<FirstType> & lhs, MathSequenceAdapter<SecondType> const& rhs)
{
    Details::assignTransform(lhs.m_values, rhs.m_values, [](auto a, auto b)
    {
        return a + b;
    });
    return lhs;
}

template<class FirstType, class SecondType>
MathSequenceAdapter<FirstType>& operator/=(MathSequenceAdapter<FirstType> & lhs, MathSequenceAdapter<SecondType> const& rhs)
{
    Details::assignTransform(lhs.m_values, rhs.m_values, [](auto a, auto b)
    {
        return a / b;
    });
    return lhs;
}


template<class FirstType, class SecondType>
MathSequenceAdapter<FirstType>& operator*=(MathSequenceAdapter<FirstType> & lhs, MathSequenceAdapter<SecondType> const& rhs)
{
    Details::assignTransform(lhs.m_values, rhs.m_values, [](auto a, auto b)
    {
        return a + b;
    });
    return lhs;
}

template<class FirstType, class SecondType>
MathSequenceAdapter<FirstType>& operator*=(MathSequenceAdapter<FirstType> & lhs, SecondType scalar)
{
    for(auto& a : lhs.m_values)
    {
        a *= scalar;
    }
    return lhs;
}

template<class FirstType, class SecondType>
MathSequenceAdapter<FirstType>& operator/=(MathSequenceAdapter<FirstType> & lhs, SecondType scalar)
{
    for(auto& a : lhs.m_values)
    {
        a /= scalar;
    }
    return lhs;
}

//template<class Type>
//using MathVectorAdapter = MathSequenceAdapter<std::vector<typename std::remove_cv<Type>::type>>;

template<class Type>
struct MathVectorAdapter : MathSequenceAdapter<std::vector<typename std::remove_cv<Type>::type>>
{
    using value_type = typename std::remove_cv<Type>::type;
    using sequence_type = std::vector<value_type>;

    template<class Container, typename=std::enable_if<std::is_same<typename std::remove_cv<typename Container::value_type>::type,
                                                                   typename std::remove_cv<value_type>::type>::value>>
    MathVectorAdapter(Container const& c)
        : MathSequenceAdapter<sequence_type>(std::begin(c), std::end(c))
    {}

    MathVectorAdapter(std::size_t numItems)
        : MathSequenceAdapter<sequence_type>(numItems)
    {}
};


template<class Type>
using MathArrayViewAdapter = MathSequenceAdapter<ArrayView<Type>>;



template<class Type>
auto make_math_vector_adapter(Type const& args)
{
    return MathVectorAdapter<typename Type::value_type>(args);
}

template<class Type>
auto make_math_adapter(Type const& args)
{
    return MathVectorAdapter<typename Type::value_type>(args);
}

template<class Type>
auto make_math_adapter(ArrayView<Type> args)
{
    return MathArrayViewAdapter<Type>(args);
}
