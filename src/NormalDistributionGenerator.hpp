#pragma once
#include <random>

template<class Type>
struct NormalDistributionGenerator
{
    NormalDistributionGenerator(uint32_t seed, Type mean, Type std)
        : m_mt(seed)
        , m_normalDist(mean, std)
    {}

    Type operator()()
    {
        return m_normalDist(m_mt);
    }

private:
    std::mt19937 m_mt;
    std::normal_distribution<Type> m_normalDist;
};
