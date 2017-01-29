#pragma once

#include <memory>
#include "NodeBuilders/NodeBuilder.hpp"
#include "IConnectedLayerOperationsFactory.hpp"

struct FullyConnectedLayerSpecs
{
    FullyConnectedLayerSpecs(
            std::unique_ptr<IConnectedLayerOperationsFactory<BNN_TYPE>> activationFactory,
            std::size_t numNeurons)
        : activationFactory(std::move(activationFactory))
        , numNeurons(numNeurons)
    {}

    std::unique_ptr<IConnectedLayerOperationsFactory<BNN_TYPE>> activationFactory;
    std::size_t numNeurons; // TODO add check for numNeurons > 0
};
