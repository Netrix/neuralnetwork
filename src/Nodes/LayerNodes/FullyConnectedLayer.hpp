#pragma once
#include "LayerNode.hpp"
#include "NotNull.hpp"
#include <algorithm>

template<class Type>
struct FullyConnectedLayerNode : LayerNode<Type>
{
    FullyConnectedLayerNode(NotNull<ComputationNode<Type>> const& inputLayer, std::size_t numOutputs)    // TODO change computation node to LayerNode? is that possible?
        : m_inputLayer(inputLayer)
        , m_outputs(numOutputs)
    {

    }

//    void forwardPass() override
//    {
//        std::transform(std::begin(m_inputs), std::end(m_inputs), std::begin(m_outputs),
//                       [](auto const& node)
//        {
//            return node->getOutputValues()[0];
//        });
//    }

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
    std::vector<Type> m_outputs;
};
