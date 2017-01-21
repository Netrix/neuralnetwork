#include "BackPropagationNetwork.hpp"


BackPropagationNetwork::BackPropagationNetwork(
        OperationNodes && operationNodes,
        ConstNodes && constNodes,
        VariableNodes && variableNodes,
        std::unique_ptr<ConstStorage<BNN_TYPE>> constStorage,
        std::unique_ptr<VariableStorage<BNN_TYPE>> variableStorage,
        std::unique_ptr<VariableDeltaStorage<BNN_TYPE>> variableDeltaStorage)
    : m_operationNodes(std::move(operationNodes))
    , m_constNodes(std::move(constNodes))
    , m_variableNodes(std::move(variableNodes))
    , m_constStorage(std::move(constStorage))
    , m_variableStorage(std::move(variableStorage))
    , m_variableDeltaStorage(std::move(variableDeltaStorage))
{}

ArrayView<BNN_TYPE const> BackPropagationNetwork::forwardPass(ArrayView<BNN_TYPE const> input)
{
    // 1. set input into m_constStorage (verify length!!!)
    // 2. run all operations one by one
    // 3. return arrayView to last operation outputs
    m_constStorage->setValues(input);
    for(auto const& operation : m_operationNodes)
    {
        operation->forwardPass();
    }
    return m_operationNodes.back()->getOutputValues();
}

void BackPropagationNetwork::backPropagate(ArrayView<BNN_TYPE> errors)
{
    m_operationNodes.back()->backPropagate(errors);
    m_numBackpropagationPasses++;
}

void BackPropagationNetwork::setVariables(ArrayView<BNN_TYPE const> values)
{
    m_variableStorage->setValues(values);
}

void BackPropagationNetwork::applyDeltaOnVariables()
{
    auto l_weights = m_variableStorage->getValues();
    std::transform(std::begin(l_weights), std::end(l_weights), std::begin(m_variableDeltaStorage->getValues()), std::begin(l_weights),
                   [=](auto a, auto b)
    {
        return a + (b / m_numBackpropagationPasses) * m_learningRate;
    });

    m_numBackpropagationPasses = 0;
    m_variableDeltaStorage->setValuesByGenerator([]
    {
        return 0.0f;
    });
}
