#pragma once
#include "NotNull.hpp"
#include "NetworkBuilder.hpp"
#include "LayeredNetworkBuilders/LayerBuilder.hpp"

struct FullyConnectedLayerSpecs;
struct FullyConnectedLayerBuilder;

struct LayeredNetworkBuilder
{
    NotNull<FullyConnectedLayerBuilder> setOutputLayer(FullyConnectedLayerSpecs const& specs);

    std::unique_ptr<BackPropagationNetwork> buildBackPropagationNetwork(BNN_TYPE learningRate=1.0f) const
    {
        return m_networkBuilder.buildBackPropagationNetwork(learningRate);
    }

    std::size_t getNumVariables() const
    {
        return m_networkBuilder.getNumVariables();
    }

private:
    NetworkBuilder m_networkBuilder;
    std::unique_ptr<LayerBuilder> m_outputLayer;
};
