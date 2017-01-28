#pragma once
#include "LayerNode.hpp"
#include "NotNull.hpp"
#include <algorithm>

template<class Type>
struct FullyConnectedLayerNode : LayerNode<Type>
{
    FullyConnectedLayerNode(NotNull<ComputationNode<Type>> const& inputLayer,
                            ArrayView<ArrayView<Type const>> weights,
                            std::size_t numOutputs)    // TODO change computation node to LayerNode? is that possible?
        : m_inputLayer(inputLayer)
        , m_outputs(numOutputs)
    {
        // 1. input are weights
        // 2. second input are previous inputs
    }

    void forwardPass() override
    {
        for(auto i = 0u; i m_outputs.size(); ++i)
        {
            m_outputs[i]  = calculateOutput()
        }
    }

//    std::size_t getNumOutputs() const override
//    {
//        return m_outputs.size();
//    }

//    ArrayView<Type const> getOutputValues() const override
//    {
//        return m_outputs;
//    }

//    void backPropagate(ArrayView<Type const> errors) override
//    {
//        for(std::size_t i = 0; i < errors.size(); ++i)
//        {
//            m_inputs[i]->backPropagate(errors[i]);
//        }
//    }

private:
    NotNull<ComputationNode<Type>> m_inputLayer;
    ArrayView<ArrayView<Type const>> m_weights;
    std::vector<Type> m_outputs;
};
