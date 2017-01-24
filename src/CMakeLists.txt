project(neural-networks)

set(NODES_FILES
    Nodes/OperationNode.hpp
    Nodes/ComputationNode.hpp
    Nodes/ConstNode.hpp
    Nodes/VariableNode.hpp
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
    Nodes/LayerNodes/LayerNode.hpp
    Nodes/LayerNodes/PassThroughLayerNode.hpp
    )

set(FILES
    ${NODES_FILES}
    NodeBuilders/UnaryNodeBuilder.cpp
    NodeBuilders/UnaryNodeBuilder.hpp
    NodeBuilders/BinaryNodeBuilder.cpp
    NodeBuilders/BinaryNodeBuilder.hpp
    NodeBuilders/NodeBuilder.hpp
    NodeBuilders/ConstNodeBuilder.hpp
    NodeBuilders/VariableNodeBuilder.hpp
    NodeBuilders/OperationNodeBuilder.hpp
    NodeBuilders/MultipleInputNodeBuilder.cpp
    NodeBuilders/MultipleInputNodeBuilder.hpp
    NodeBuilders/LayerNodeBuilder.cpp
    NodeBuilders/LayerNodeBuilder.hpp
    LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp
    LayeredNetworkBuilders/FullyConnectedLayerBuilder.cpp
    LayeredNetworkBuilders/LayerBuilder.hpp
    LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp
    LayeredNetworkBuilders/InputLayerSpecs.hpp
    LayerNodeFactories/PassThrough.hpp
    Datasets/MnistLoader.cpp
    Datasets/MnistLoader.hpp
    ArrayView.hpp
    NotNull.hpp
    BuilderStorage.cpp
    BuilderStorage.hpp
    BuilderToNodeMaps.hpp
    BackPropagationNetwork.hpp
    BackPropagationNetwork.cpp
    BinaryOperationsFactory.hpp
    ConstStorageBuilder.hpp
    NodeTags.hpp
    NetworkBuilder.cpp
    NetworkBuilder.hpp
    ScalarStorage.hpp
    MathVectorAdapter.hpp
    StreamOperators.hpp
    VariableStorage.hpp
    VariableStorageBuilder.hpp
    UnaryOperationsFactory.hpp
    MultipleInputOperationsFactory.hpp
    ConstStorage.hpp
    LayeredNetworkBuilder.cpp
    LayeredNetworkBuilder.hpp
    ILayerOperationsFactory.hpp
    NormalDistributionGenerator.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library("${PROJECT_NAME}-lib" ${FILES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}-lib")


# For Visual Studio
source_group(src FILES ${SOURCES})
