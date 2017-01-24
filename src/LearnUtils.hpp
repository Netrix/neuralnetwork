#pragma once
#include "NodeBuilders/NodeBuilder.hpp"
#include "MathVectorAdapter.hpp"
#include "NormalDistributionGenerator.hpp"
#include "BackPropagationNetwork.hpp"
#include <iostream>
#include <future>
#include <algorithm>
#include <numeric>

template<class Type>
struct BatchResult
{
    MathVectorAdapter<Type> weightDelta;
    Type error;
};

struct Task
{
    std::size_t batchStart;
    std::size_t batchEnd;
};

template<class Dataset, class Type>
struct BatchJob
{
    using ResultType = BatchResult<Type>;

    BatchJob(Dataset const& dataset, std::unique_ptr<BackPropagationNetwork> network)
        : m_dataset(dataset)
        , m_network(std::move(network))
    {
        m_jobThread = std::thread([this]
        {
            while(m_isRunning)
            {
                auto future = m_taskPromise.get_future();
                auto task = future.get();

                if(m_isRunning)
                {
                    break;
                }

                Type errorSum{};
                for(std::size_t k = task.batchStart; k < task.batchEnd; ++k)
                {
                    auto result = make_math_adapter(m_network->forwardPass(m_dataset.getInputSample(k)));
                    auto expected = make_math_adapter(m_dataset.getOutputSample(k));
                    auto error = expected - result;
                    m_network->backPropagate(error);

                    auto squaredError = error * error;
                    errorSum += squaredError.sum();
                }

                m_taskPromise = {};
                m_resultPromise.set_value(BatchResult<Type>{m_network->getVariableDeltas(), errorSum});
            }
        });
    }

    ~BatchJob()
    {
        m_isRunning = false;
        m_jobThread.join();
    }

    void startBatch(std::size_t batchStart, std::size_t batchEnd)
    {
        m_resultPromise = {};
        m_taskPromise.set_value(Task{batchStart, batchEnd});
    }

    ResultType getResults()
    {
        return m_resultPromise.get_future().get();
    }

    void setWeights(ArrayView<Type const> weights)
    {
        m_network->setVariables(weights);
    }

private:
    Dataset const& m_dataset;
    std::unique_ptr<BackPropagationNetwork> m_network;
    std::thread m_jobThread;
    std::promise<Task> m_taskPromise;
    std::promise<ResultType> m_resultPromise;
    std::atomic<bool> m_isRunning{true};
};

template<class Dataset, class Network>
auto learnEpoch(Network & network, Dataset const& dataset, std::size_t batchSize)
{
    BNN_TYPE errorSum = 0;
    for(std::size_t i = 0; i < dataset.getNumSamples();)
    {
        for(std::size_t k = 0; k < batchSize && i < dataset.getNumSamples(); ++i, ++k)
        {
            auto result = make_math_adapter(network->forwardPass(dataset.getInputSample(i)));
            auto expected = make_math_adapter(dataset.getOutputSample(i));
            auto error = expected - result;
            network->backPropagate(error);

            auto squaredError = error * error;
            errorSum += squaredError.sum();
        }
        network->applyDeltaOnVariables();
        std::cout << "batch completed, samples passed: " << i << "/" << dataset.getNumSamples() << std::endl;
    }
    return errorSum;
}


template<class Dataset, class NetworkBuilder>
auto learnEpochParallel(NetworkBuilder & networkBuilder, Dataset const& dataset, std::size_t batchSize, float learningRate)
{
    auto numThreads = std::max(2u, std::thread::hardware_concurrency());
    std::vector<std::unique_ptr<BatchJob<Dataset, BNN_TYPE>>> jobs;
    for(auto i = 0u; i < numThreads; ++i)
    {
        auto network = networkBuilder.buildBackPropagationNetwork(learningRate);
        jobs.emplace_back(std::make_unique<BatchJob<Dataset, BNN_TYPE>>(dataset, std::move(network)));
    }

    auto mainNetwork = networkBuilder.buildBackPropagationNetwork(learningRate);
    mainNetwork->setVariables(NormalDistributionGenerator<BNN_TYPE>(13, 0, 1));

    while((batchSize % numThreads) != 0)
    {
        batchSize--;
    }

    auto numSamplesPerBatch = batchSize / numThreads;

    auto weights = make_math_adapter(mainNetwork->getVariables());

    BNN_TYPE errorSum = 0;
    for(std::size_t i = 0; i < dataset.getNumSamples();)
    {
        if(dataset.getNumSamples() - i <= batchSize)
        {
            for(int k = 0; k < jobs.size(); ++k, i += numSamplesPerBatch)
            {
                jobs[k]->setWeights(mainNetwork->getVariables());
                jobs[k]->startBatch(i, i + numSamplesPerBatch);
            }

            for(int k = 0; k < jobs.size(); ++k)
            {
                auto result = jobs[k]->getResults();
                weights += result.weightDelta;
                errorSum += result.error;
            }
        }
        else
        {
            for(std::size_t k = 0; k < batchSize && i < dataset.getNumSamples(); i += batchSize)
            {
                auto result = make_math_adapter(mainNetwork->forwardPass(dataset.getInputSample(i)));
                auto expected = make_math_adapter(dataset.getOutputSample(i));
                auto error = expected - result;
                mainNetwork->backPropagate(error);

                auto squaredError = error * error;
                errorSum += squaredError.sum();
            }
            mainNetwork->applyDeltaOnVariables();
        }
    }
    return errorSum;
}
