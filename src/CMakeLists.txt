project(neural-networks)

set(NODES_FILES
    Nodes/OperationNode.hpp
    Nodes/ComputationNode.hpp
    Nodes/ConstNode.hpp
    Nodes/ConstSingleValueNode.hpp
    Nodes/ConstBufferNode.hpp
    Nodes/VariableNode.hpp
    Nodes/VariableBufferNode.hpp
    Nodes/VariableSingleValueNode.hpp
    Nodes/UnaryOperations/UnaryOperationNode.hpp
    Nodes/UnaryOperations/SigmoidUnaryOperation.hpp
    Nodes/UnaryOperations/TanhUnaryOperation.hpp
    Nodes/UnaryOperations/ReLUUnaryOperation.hpp
    Nodes/UnaryOperations/PReLUUnaryOperation.hpp
    Nodes/BinaryOperations/AddBinaryOperation.hpp
    Nodes/BinaryOperations/MulBinaryOperation.hpp
    Nodes/BinaryOperations/BinaryOperationNode.hpp
    Nodes/MultipleInputOperators/AddOperation.hpp
    Nodes/MultipleInputOperators/MultipleInputOperationNode.hpp
    Nodes/MultipleInputLayerNodes/MultipleInputLayerNode.hpp
    Nodes/MultipleInputLayerNodes/PassThroughMultipleInputLayerNode.hpp
    Nodes/LayerNodes/LayerNode.hpp
    Nodes/LayerNodes/FullyConnectedLayer.hpp
    Nodes/LayerNodes/SigmoidLayer.hpp
    Nodes/LayerNodes/ReLULayer.hpp
    Nodes/LayerNodes/TanhLayer.hpp
    Nodes/SingleOutputOperationNode.hpp
    )

set(FILES
    ${NODES_FILES}
    NodeBuilders/UnaryNodeBuilder.cpp
    NodeBuilders/UnaryNodeBuilder.hpp
    NodeBuilders/BinaryNodeBuilder.cpp
    NodeBuilders/BinaryNodeBuilder.hpp
    NodeBuilders/NodeBuilder.hpp
    NodeBuilders/ConstNodeBuilder.hpp
    NodeBuilders/ConstSingleValueNodeBuilder.hpp
    NodeBuilders/ConstBufferNodeBuilder.hpp
    NodeBuilders/VariableNodeBuilder.hpp
    NodeBuilders/OperationNodeBuilder.hpp
    NodeBuilders/MultipleInputNodeBuilder.cpp
    NodeBuilders/MultipleInputNodeBuilder.hpp
    NodeBuilders/MultipleInputLayerNodeBuilder.cpp
    NodeBuilders/MultipleInputLayerNodeBuilder.hpp
    NodeBuilders/ConnectedLayerNodeBuilder.cpp
    NodeBuilders/ConnectedLayerNodeBuilder.hpp
    NodeBuilders/PassThroughLayerNodeBuilder.cpp
    NodeBuilders/PassThroughLayerNodeBuilder.hpp
    NodeBuilders/VariableBufferNodeBuilder.hpp
    NodeBuilders/VariableSingleValueNodeBuilder.hpp
    LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp
    LayeredNetworkBuilders/FullyConnectedLayerBuilder.cpp
    LayeredNetworkBuilders/LayerBuilder.hpp
    LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp
    LayeredNetworkBuilders/InputLayerSpecs.hpp
    MultipleInputLayerNodeFactories/PassThrough.hpp
    MultipleInputLayerNodeFactories/IMultipleInputLayerOperationsFactory.hpp
    PassThroughLayerNodeFactories/SigmoidLayer.hpp
    PassThroughLayerNodeFactories/ReLULayer.hpp
    PassThroughLayerNodeFactories/TanhLayer.hpp
    PassThroughLayerNodeFactories/IPassThroughLayerNodeFactory.hpp
    Datasets/MnistLoader.cpp
    Datasets/MnistLoader.hpp
    UnaryOperationNodesFactories/IUnaryOperationNodesFactory.hpp
    UnaryOperationNodesFactories/SigmoidNodeFactory.hpp
    UnaryOperationNodesFactories/TanhNodeFactory.hpp
    UnaryOperationNodesFactories/ReLUNodeFactory.hpp
    UnaryOperationNodesFactories/PReLUNodeFactory.hpp
    BinaryOperationNodesFactories/IBinaryOperationNodesFactory.hpp
    BinaryOperationNodesFactories/MulNodeFactory.hpp
    BinaryOperationNodesFactories/AddNodeFactory.hpp
    MultipleInputOperationNodesFactories/IMultipleInputOperationNodesFactory.hpp
    MultipleInputOperationNodesFactories/AddNodeFactory.hpp
    ConnectedLayerNodeFactories/FullyConnectedLayer.hpp
    ConnectedLayerNodeFactories/IConnectedLayerNodeFactory.hpp
    BuilderStorage.cpp
    BuilderStorage.hpp
    BuilderToNodeMaps.hpp
    BackPropagationNetwork.hpp
    BackPropagationNetwork.cpp
    ConstStorageBuilder.hpp
    NodeSpecs.hpp
    NetworkBuilder.cpp
    NetworkBuilder.hpp
    ScalarStorage.hpp
    StreamOperators.hpp
    VariableStorage.hpp
    VariableStorageBuilder.hpp
    ConstStorage.hpp
    LayeredNetworkBuilder.cpp
    LayeredNetworkBuilder.hpp
    NormalDistributionGenerator.hpp
    MnistPreprocessedDataSet.hpp
    LearnUtils.hpp
    ModelData.hpp
    Utils/Math.cpp
    Utils/Math.hpp
    Utils/MathVectorAdapter.hpp
    Utils/ArrayView.hpp
    Utils/NotNull.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library("${PROJECT_NAME}-lib" ${FILES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}-lib")


# For Visual Studio
source_group(src FILES ${SOURCES})
