project(neural-networks)

add_definitions(-std=c++14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(FILES
    NodeBuilders/UnaryNodeBuilder.cpp
    NodeBuilders/UnaryNodeBuilder.hpp
    NodeBuilders/BinaryNodeBuilder.cpp
    NodeBuilders/BinaryNodeBuilder.hpp
    NodeBuilders/NodeBuilder.hpp
    NodeBuilders/ConstNodeBuilder.hpp
    NodeBuilders/VariableNodeBuilder.hpp
    NodeBuilders/OperationNodeBuilder.hpp
    UnaryOperations/UnaryOperationNode.hpp
    UnaryOperations/SigmoidUnaryOperation.hpp
    BinaryOperations/AddBinaryOperation.hpp
    BinaryOperations/MulBinaryOperation.hpp
    BinaryOperations/BinaryOperationNode.hpp
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
    ConstStorage.hpp
    main.cpp
)
add_executable(${PROJECT_NAME} ${FILES})
