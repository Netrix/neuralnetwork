#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "ArrayView.hpp"
#include "Nodes/OperationNode.hpp"
#include "Nodes/ConstNode.hpp"
#include "Nodes/VariableNode.hpp"
#include "ConstStorage.hpp"
#include "VariableStorage.hpp"
#include "NodeBuilders/NodeBuilder.hpp" //BNN_TYPE

using OperationNodes = std::vector<std::unique_ptr<OperationNode<BNN_TYPE>>>;
using ConstNodes = std::vector<std::unique_ptr<ConstNode<BNN_TYPE>>>;
using VariableNodes = std::vector<std::unique_ptr<VariableNode<BNN_TYPE>>>;

struct BackPropagationNetwork
{
    BackPropagationNetwork(
            OperationNodes && operationNodes,
            ConstNodes && constNodes,
            VariableNodes && variableNodes,
            std::unique_ptr<ConstStorage<BNN_TYPE>> constStorage,
            std::unique_ptr<VariableStorage<BNN_TYPE>> variableStorage,
            std::unique_ptr<VariableDeltaStorage<BNN_TYPE>> variableDeltaStorage,
            BNN_TYPE learningRate);

    ArrayView<BNN_TYPE const> forwardPass(ArrayView<BNN_TYPE const> input);
    void backPropagate(ArrayView<BNN_TYPE const> errors);

    void setLearningRate(BNN_TYPE learningRate);
    void setVariables(ArrayView<BNN_TYPE const> values);
    void setVariables(std::function<BNN_TYPE()> generator);
    void applyDeltaOnVariables();

    ArrayView<BNN_TYPE const> getVariables() const;
    ArrayView<BNN_TYPE const> getVariableDeltas() const;

private:
    std::size_t m_numBackpropagationPasses = 0;
    OperationNodes m_operationNodes;
    ConstNodes m_constNodes;
    VariableNodes m_variableNodes;
    std::unique_ptr<ConstStorage<BNN_TYPE>> m_constStorage;
    std::unique_ptr<VariableStorage<BNN_TYPE>> m_variableStorage;   // teoretically no need for unique_ptr
    std::unique_ptr<VariableDeltaStorage<BNN_TYPE>> m_variableDeltaStorage;
    BNN_TYPE m_learningRate = 1.0f;
};
