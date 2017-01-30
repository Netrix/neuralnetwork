#pragma once

#include <memory>
#include "NodeBuilders/NodeBuilder.hpp"
#include "PassThroughLayerNodeFactories/IPassThroughLayerNodeFactory.hpp"

struct FullyConnectedLayerSpecs
{
    FullyConnectedLayerSpecs(
            std::unique_ptr<IPassThroughLayerNodeFactory<BNN_TYPE>> activationFactory,
            std::size_t numNeurons)
        : activationFactory(std::move(activationFactory))
        , numNeurons(numNeurons)
    {
        assert(numNeurons > 0);
    }

    std::unique_ptr<IPassThroughLayerNodeFactory<BNN_TYPE>> activationFactory;
    std::size_t numNeurons;
};
