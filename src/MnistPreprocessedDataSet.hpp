#pragma once
#include "Datasets/MnistLoader.hpp"
#include "Utils/ArrayView.hpp"
#include <algorithm>
#include <vector>

template<class Type>
struct MnistPreprocessedDataSet
{
    MnistPreprocessedDataSet(MnistDataset const& mnistData)
        : m_numSamples(mnistData.labels.size())
        , m_inputSampleSize(mnistData.imageWidth * mnistData.imageHeight)
        , m_inputData(mnistData.imageData.size())
        , m_outputData(m_outputSampleSize * mnistData.labels.size())
    {
        assert(mnistData.labels.size() == (mnistData.imageData.size() / m_inputSampleSize));

        std::transform(std::begin(mnistData.imageData), std::end(mnistData.imageData), std::begin(m_inputData),
                       [](auto v)
        {
            return (static_cast<Type>(v) / 255.0) - 0.5;
        });

        for(std::size_t i = 0, v = 0; i < m_outputData.size(); ++v)
        {
            for(std::size_t k = 0; k < 10; ++k, ++i)
            {
                m_outputData[i] = mnistData.labels[v] == k ? 1.0 : 0.0;
            }
        }
    }

    auto getInputSampleSize() const
    {
        return m_inputSampleSize;
    }

    auto getOutputSampleSize() const
    {
        return m_outputSampleSize;
    }

    auto getInputSample(std::size_t sampleIndex) const
    {
        return ArrayView<Type const>(m_inputData.data() + m_inputSampleSize * sampleIndex, m_inputSampleSize);
    }

    auto getOutputSample(std::size_t sampleIndex) const
    {
        return ArrayView<Type const>(m_outputData.data() + m_outputSampleSize * sampleIndex, m_outputSampleSize);
    }

    auto getNumSamples() const
    {
        return m_numSamples;
    }

private:
    std::size_t m_numSamples;

    std::size_t m_inputSampleSize;
    std::vector<Type> m_inputData;

    std::size_t m_outputSampleSize = 10;
    std::vector<Type> m_outputData;
};
