#pragma once

#include <memory>
#include "NodeBuilders/NodeBuilder.hpp"
#include "IPassThroughLayerOperationsFactory.hpp"

struct FullyConnectedLayerSpecs
{
    FullyConnectedLayerSpecs(
            std::unique_ptr<IPassThroughLayerOperationsFactory<BNN_TYPE>> activationFactory,
            std::size_t numNeurons)
        : activationFactory(std::move(activationFactory))
        , numNeurons(numNeurons)
    {
        assert(numNeurons > 0);
    }

    std::unique_ptr<IPassThroughLayerOperationsFactory<BNN_TYPE>> activationFactory;
    std::size_t numNeurons;
};
