#pragma once

#include <memory>
#include "NodeBuilders/NodeBuilder.hpp"
#include "ILayerOperationsFactory.hpp"

struct FullyConnectedLayerSpecs
{
    std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> activationFactory;
//    std::size_t numNeurons; // TODO add check for numNeurons > 0
};
