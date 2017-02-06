#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "Utils/ArrayView.hpp"

template<class Type>
struct ModelData
{
    ModelData(std::size_t numVariables)
        : m_data(numVariables)
    {
    }

    ModelData(ArrayView<Type const> data)
        : m_data(std::begin(data), std::end(data))
    {
    }

    void load(std::string const& modelPath)
    {
        std::ifstream inFile(modelPath);
        std::size_t numVariables;
        inFile >> numVariables;
        assert(numVariables == m_data.size());

        std::copy_n(std::istream_iterator<Type>(inFile), m_data.size(), std::begin(m_data));
    }

    void save(std::string const& modelPath) const
    {
        std::ofstream outFile(modelPath);
        outFile << m_data.size();
        std::copy_n(std::begin(m_data), m_data.size(), std::ostream_iterator<Type>(outFile));
    }

    ArrayView<Type const> getData() const
    {
        return m_data;
    }

private:
    std::vector<Type> m_data;
};

bool modelFileExists(std::string const& modelPath)
{
    std::ifstream inFile(modelPath);
    return inFile.good();
}
