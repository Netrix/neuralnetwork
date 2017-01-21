project(neural-networks)

set(FILES
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
    UnaryOperations/UnaryOperationNode.hpp
    UnaryOperations/SigmoidUnaryOperation.hpp
    UnaryOperations/TanhUnaryOperation.hpp
    UnaryOperations/ReLUUnaryOperation.hpp
    BinaryOperations/AddBinaryOperation.hpp
    BinaryOperations/MulBinaryOperation.hpp
    BinaryOperations/BinaryOperationNode.hpp
    MultipleInputOperators/AddOperation.hpp
    MultipleInputOperators/MultipleInputOperationNode.hpp
    ArrayView.hpp
    NotNull.hpp
    BuilderStorage.cpp
    BuilderStorage.hpp
    BuilderToNodeMaps.hpp
    BackPropagationNetwork.hpp
    BackPropagationNetwork.cpp
    OperationNode.hpp
    ComputationNode.hpp
    BinaryOperationsFactory.hpp
    ConstNode.hpp
    ConstStorageBuilder.hpp
    NodeTags.hpp
    NetworkBuilder.cpp
    NetworkBuilder.hpp
    VariableNode.hpp
    ScalarStorage.hpp
    VariableStorage.hpp
    VariableStorageBuilder.hpp
    UnaryOperationsFactory.hpp
    MultipleInputOperationsFactory.hpp
    ConstStorage.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library("${PROJECT_NAME}-lib" ${FILES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}-lib")


# For Visual Studio
source_group(src FILES ${SOURCES})
