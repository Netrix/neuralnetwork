#pragma once
#include "LayerNode.hpp"
#include "Nodes/VariableNode.hpp"
#include "Utils/NotNull.hpp"
#include "Utils/Math.hpp"
#include <algorithm>

using MatrixMultiplyFunction = void(ArrayView<float const> inputVector,
                               ArrayView<float const> weightsMatrix,
                               ArrayView<float> outputVector);

template<class Type>
struct FullyConnectedLayerNode : LayerNode<Type>
{
    FullyConnectedLayerNode(NotNull<ComputationNode<Type>> inputLayer,
                            NotNull<VariableNode<Type>> variables,
                            std::size_t numOutputs,
                            MatrixMultiplyFunction* matrixMultiplyFunction)
        : m_inputLayer(inputLayer)
        , m_weights(variables)
        , m_errorsForInput(inputLayer->getNumOutputs())
        , m_errorsForWeights(variables->getNumOutputs())
        , m_outputs(numOutputs)
        , m_matrixMultiplyFunction(matrixMultiplyFunction)
    {
    }

    void forwardPass() override
    {
        m_matrixMultiplyFunction(m_inputLayer->getOutputValues(),
                                 m_weights->getOutputValues(),
                                 m_outputs);
        resetErrorsForInput();
    }

    std::size_t getNumOutputs() const override
    {
        return m_outputs.size();
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return m_outputs;
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        for(std::size_t i = 0; i < errors.size(); ++i)
        {
            backPropagateSingleError(errors[i], getNthLayerWeights(i), getNthLayerWeightsErrors(i));
        }
    }

    void backPropagationPass() override
    {
        m_inputLayer->backPropagate(m_errorsForInput);
        m_weights->backPropagate(m_errorsForWeights);
    }

private:
    void resetErrorsForInput()
    {
        std::fill(std::begin(m_errorsForInput), std::end(m_errorsForInput), Type{});
        std::fill(std::begin(m_errorsForWeights), std::end(m_errorsForWeights), Type{});
    }

    void backPropagateSingleError(Type error, ArrayView<Type const> weights, ArrayView<Type> deltas)
    {
        auto inputs = m_inputLayer->getOutputValues();
        deltas[0] += error;
        for(auto i = 0u; i < inputs.size(); ++i)
        {
            m_errorsForInput[i] += error * weights[i + 1];
            deltas[i + 1] += error * inputs[i];
        }
    }

    Type calculateSingleOutput(ArrayView<Type const> input, ArrayView<Type const> weights) const
    {
        Type output = weights[0];
        for(auto i = 0; i < input.size(); ++i)
        {
            output += input[i] * weights[i + 1];
        }
        return output;
    }

    ArrayView<Type const> getNthLayerWeights(std::size_t layerIndex) const
    {
        auto layerSize =(m_inputLayer->getNumOutputs() + 1);
        auto layerStart = layerSize * layerIndex;
        return m_weights->getOutputValues()(layerStart, layerStart + layerSize);
    }

    ArrayView<Type> getNthLayerWeightsErrors(std::size_t layerIndex)
    {
        auto layerSize =(m_inputLayer->getNumOutputs() + 1);
        auto layerStart = layerSize * layerIndex;
        return ArrayView<Type>(m_errorsForWeights)(layerStart, layerStart + layerSize);
    }

private:
    NotNull<ComputationNode<Type>> m_inputLayer;
    NotNull<VariableNode<Type>> m_weights;
    std::vector<Type> m_errorsForInput;
    std::vector<Type> m_errorsForWeights;
    std::vector<Type> m_outputs;
    MatrixMultiplyFunction* m_matrixMultiplyFunction;
};
